//
//  JJB2Engine.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2Engine.h"
#include "JJB2WorldContractListener.h"
#include "JJB2ShapeCache.h"
#include "JJB2Config.h"
#include "JJB2Node.h"

static JJB2Engine* instance = 0;

JJB2Engine* JJB2Engine::sharedInstance()
{
    
    if (!instance)
    {
        instance = new JJB2Engine;
        instance->init();
    }
    return instance;
}

JJB2Engine::JJB2Engine():m_isStop(false)
{
    
}

JJB2Engine::~JJB2Engine()
{
    
}

void JJB2Engine::purcheEngine()
{
    if (instance)
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(JJB2Engine::step), instance);
        
        instance->deleteWorld();
        
        instance->release();
        instance = nullptr;
    }
}

void JJB2Engine::init()
{
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
    
    // get ptmRatio from GB2ShapeCache
    if(GB2_HIGHRES_PHYSICS_SHAPES)
    {
        PTM_RATIO =  JJB2ShapeCache::shareInstance()->getptmRatio() / 2.0f;
    }
    else
    {
        PTM_RATIO =  JJB2ShapeCache::shareInstance()->getptmRatio();
    }
    
    // set the contact listener
    worldContactListener = new JJB2WorldContractListener();
    world->SetContactListener(worldContactListener);
    
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule(schedule_selector(JJB2Engine::step), this, 1 / 60.0f, false);
}

void JJB2Engine::stopWorldUpdate()
{
    if (!m_isStop)
    {
        m_isStop = !m_isStop;
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(JJB2Engine::step), this);
    }
}


void JJB2Engine::startWorldUpdate()
{
    if (m_isStop)
    {
        m_isStop = !m_isStop;
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->schedule(schedule_selector(JJB2Engine::step), this, 1 / 60.0f, false);
    }
}

void JJB2Engine::step(float dt)
{
    if (!world)
    {
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(JJB2Engine::step), this);
        return;
    }
    
    const float32 timeStep = 1.0f / 30.0f;
    const int32 velocityIterations = 5;
    const int32 positionIterations = 1;
    
    // step the world
    world->Step(timeStep, velocityIterations, positionIterations);
    
    this->iterateObjectsWithBlock([this](JJB2Node* o)
                                  {
                                       o->updateCCFromPhysics();
									   if(o->getDeleteLater())
                                       {
                                           o->deleteNow();
                                       }
                                  });
}

void JJB2Engine::deleteWorld()
{
    this->deleteAllObjects();
    // delete the world
    delete world;
    world = NULL;
    
    // delete the contact listener
    delete worldContactListener;
    worldContactListener = NULL;
}


void JJB2Engine::deleteAllObjects()
{
    // iterate all bodies
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        JJB2Node *o = (JJB2Node*)(b->GetUserData());
        if(o)
        {
            // destroy physics object
            o->deleteNow();
        }
        else
        {
            // destroy body
            world->DestroyBody(b);
        }
    }
}

void JJB2Engine::iterateObjectsWithBlock(JJB2NodeCallBack aCallBack)
{
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
		JJB2Node* node =(JJB2Node*)(b->GetUserData());

		if (node)
		{
			aCallBack(node);
		}
    }
}

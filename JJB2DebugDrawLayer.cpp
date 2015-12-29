//
//  JJB2DebugDrawLayer.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/13.
//
//

#include "JJB2DebugDrawLayer.h"
#include "JJB2Engine.h"

USING_NS_CC;

bool JJB2DebugDrawLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    // take world from the singleton
    world = JJB2Engine::sharedInstance()->getworld();
    
    // Enable debug draw
    debugDraw = new GLESDebugDraw(PTM_RATIO);
    world->SetDebugDraw(debugDraw);
    
    // Set the flags
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    // flags += b2DebugDraw::e_aabbBit;
    flags += b2Draw::e_centerOfMassBit;
    
    debugDraw->SetFlags(flags);
    
//    if(isDebug && NULL == m_debugDraw)
//    {
//        m_debugDraw = new GLESDebugDraw(PTM_RATIO);
//        m_world->SetDebugDraw(m_debugDraw);
//        
//        uint32 flags = 0;
//        flags += b2Draw::e_shapeBit;
//        flags += b2Draw::e_jointBit;
//        flags += b2Draw::e_pairBit;
//        flags += b2Draw::e_centerOfMassBit;
//        m_debugDraw->SetFlags(flags);
//    }
    return true;
}

JJB2DebugDrawLayer::~JJB2DebugDrawLayer()
{
    // remove debug draw from the world
    world->SetDebugDraw(0);
    
    // delete debug draw
    delete debugDraw;
}

void JJB2DebugDrawLayer::draw(cocos2d::Renderer *renderer,
                              const cocos2d::Mat4 &transform,
                              bool transformUpdated)
{
    Layer::draw(renderer, transform, transformUpdated);
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    _modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(JJB2DebugDrawLayer::onDraw, this);
    renderer->addCommand(&_customCommand);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void JJB2DebugDrawLayer::onDraw()
{
    if (world)
    {
        Director* director = Director::getInstance();
        CCASSERT(nullptr != director, "Director is null when seting matrix stack");
        Mat4 oldMV;
        oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
        
        world->DrawDebugData();
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
    }
}


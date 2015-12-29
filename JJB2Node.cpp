//
//  JJB2Node.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2Node.h"
#include "JJB2Engine.h"

float PTM_RATIO = 32.0f;

JJB2Node::JJB2Node():
isUpdatePos(true)
{
	deleteLater = false;
	ccNode = nullptr;
}

JJB2Node::~JJB2Node()
{
	CC_SAFE_RELEASE(ccNode);
}

bool JJB2Node::initWithNode(Node* node)
{
    this->initWithShape(std::string(), b2_dynamicBody, node);
    return true;
}

bool JJB2Node::initWithDynamicBody(const std::string& shape,Node* node)
{
    this->initWithShape(shape, b2_dynamicBody, node);
    return true;
}

bool JJB2Node::initWithStaticBody(const std::string& shape, Node*node)
{
    this->initWithShape(shape, b2_staticBody, node);
    return true;
}

bool JJB2Node::initWithKinematicBody(const std::string& shape, Node*node)
{
    this->initWithShape(shape, b2_kinematicBody, node);
    return true;
}

bool JJB2Node::initWithShape(const std::string& shape, b2BodyType bodyType ,Node* node)
{
    world = JJB2Engine::sharedInstance()->getworld();
    
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(0,0);
    bodyDef.angle = 0;
    body = world->CreateBody(&bodyDef);
    
    // set user data and retain self
    this->retain();
    body->SetUserData(this);
    
    // set the node
    ccNode = node;
    
    if (ccNode)
    {
        ccNode->retain();
    }
    
    if (!shape.empty())
    {
         this->setBodyShape(shape);
    }
    return true;
}


b2Fixture* JJB2Node::addFixture(b2FixtureDef* fixtureDef)
{
    return body->CreateFixture(fixtureDef);
}


Action* JJB2Node::runAction(Action* action)
{
    return ccNode->runAction(action);
}


void JJB2Node::stopAllActions()
{
    ccNode->stopAllActions();
}

void JJB2Node::stopAction(Action*  action)
{
    ccNode->stopAction(action);
}

void JJB2Node::setVisible(bool isVisible)
{
    ccNode->setVisible(isVisible);
}

void JJB2Node::setAngle(float angle)
{
    body->SetTransform(body->GetWorldCenter(), angle);
}

void JJB2Node::setCcPosition(Vec2 p)
{
    assert(body);
    ccNode->setPosition(p);
    body->SetTransform(b2Vec2FromVec2(p), body->GetAngle());
}

void JJB2Node::setScale(float scale)
{
    ccNode->setScale(scale);
}


const Vec2& JJB2Node::ccPosition()
{
    return ccNode->getPosition();
}


void JJB2Node::deleteNow()
{
    if (ccNode)
    {
        if (ccNode->getReferenceCount() >= 2)
        {
            ccNode->removeFromParentAndCleanup(true);
        }
        
        ccNode->release();
        ccNode = nullptr;
    }
    // delete the body
    this->destroyBody();
}


bool JJB2Node::isAwake()
{
    return body->IsAwake();
}

void JJB2Node::updateCCFromPhysics()
{
    b2Vec2 position = body->GetPosition();
    if (ccNode)
    {
        if (isUpdatePos)
        {
             ccNode->setPosition(Vec2(PTM_RATIO*position.x, PTM_RATIO*position.y));
		}
        else
        {
            this->setCcPosition(this->getCcNode()->getPosition());
        }
        ccNode->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
    }
}

void JJB2Node::setBodyShape(const std::string& shapeName)
{
    b2Fixture *f;
    while((f = body->GetFixtureList()))
    {
        body->DestroyFixture(f);
    }
    
    if(!shapeName.empty())
    {
        JJB2ShapeCache *shapeCache = JJB2ShapeCache::shareInstance();
        shapeCache->addFixturesToBody(body, shapeName);
        ccNode->setAnchorPoint(shapeCache->anchorPointForShape(shapeName));
    }
}


float JJB2Node::mass()
{
    assert(body);
    return body->GetMass();
}


b2Vec2 JJB2Node::physicsPosition()
{
    assert(body);
    return body->GetPosition();
}


void JJB2Node::setPhysicsPosition(b2Vec2 position)
{
    assert(body);
    ccNode->setPosition(Vec2Fromb2Vec2(position));
    body->SetTransform(position, body->GetAngle());
}


b2Vec2 JJB2Node::worldCenter()
{
    assert(body);
    return body->GetWorldCenter();
}

void JJB2Node::setBody(const std::string& shapeName,b2BodyType bodyType, b2Vec2 pos)
{
    assert(body);
    this->setBodyShape(shapeName);
    this->setBodyType(bodyType);
    this->setPhysicsPosition(pos);
}

void JJB2Node::setKinematicBody(const std::string& shapeName,b2Vec2 position)
{
    this->setBody(shapeName, b2_kinematicBody, position);
}

void JJB2Node::setDynamicBody(const std::string& shapeName, b2Vec2 position)
{
    this->setBody(shapeName, b2_dynamicBody, position);
}


void JJB2Node::setStaticBody(const std::string& shapeName, b2Vec2 position)
{
    this->setBody(shapeName, b2_staticBody, position);
}

void JJB2Node::setBodyType(b2BodyType bodyType)
{
    assert(body);
    body->SetType(bodyType);
}

void JJB2Node::applyLinearImpulse(b2Vec2 impulse,b2Vec2 point)
{
    assert(body);
    body->ApplyLinearImpulse(impulse, point, true);
}


void JJB2Node::setLinearVelocity(b2Vec2 velocity)
{
    assert(body);
    body->SetLinearVelocity(velocity);
}

void JJB2Node::setFixedRotation(bool fixedRotation)
{
    assert(body);
    body->SetFixedRotation(fixedRotation);
}

void JJB2Node::setLinearDamping(float linearDamping)
{
     assert(body);
     body->SetLinearDamping(linearDamping);
}

void JJB2Node::setAngularDamping(float angularDamping)
{
    assert(body);
    body->SetAngularDamping(angularDamping);
}

void JJB2Node::applyForce(b2Vec2 force, b2Vec2 point)
{
    assert(body);
    body->ApplyForce(force, point, true);
}

float JJB2Node::angle()
{
    assert(body);
    return body->GetAngle();
}

void JJB2Node::setTransform(b2Vec2 pos,float angle)
{
    assert(body);
    body->SetTransform(pos, angle);
}

bool JJB2Node::active()
{
    assert(body);
    return body->IsActive();
}

void JJB2Node::setActive(bool isActive)
{
    assert(body);
    body->SetActive(isActive);
}

bool JJB2Node::awake()
{
    assert(body);
    return body->IsAwake();
}

b2Vec2 JJB2Node::linearVelocity()
{
    assert(body);
    return body->GetLinearVelocity();
}

void JJB2Node::setBullet(bool bulletFlag)
{
    assert(body);
    body->SetBullet(bulletFlag);
}

void JJB2Node::destroyBody()
{
    if(body)
    {
        world->DestroyBody(body);
        body = 0;
        this->release();
    }
}

float JJB2Node::widthInM()
{
    return ccNode->getContentSize().width / PTM_RATIO;
}


void JJB2Node::clrCollisionMaskBits(uint16 bits)
{
    this->clrCollisionMaskBits(bits,std::string());
}


void JJB2Node::clrCollisionMaskBits(uint16 bits,const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() || (fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits &= ~bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


void JJB2Node::addCollisionMaskBits(uint16 bits)
{
    this->addCollisionMaskBits(bits, std::string());
}


void JJB2Node::addCollisionMaskBits(uint16 bits,const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() || (fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits |= bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


void JJB2Node::setCollisionMaskBits(uint16 bits)
{
    this->setCollisionMaskBits(bits, std::string());
}


void JJB2Node::setCollisionMaskBits(uint16 bits, const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() ||(fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.maskBits = bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


void JJB2Node::addCollisionCategoryBits(uint16 bits)
{
    this->addCollisionCategoryBits(bits, std::string());
}


void JJB2Node::addCollisionCategoryBits(uint16 bits,const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() ||(fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits |= bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


void JJB2Node::clrCollisionCategoryBits(uint16 bits)
{
    this->clrCollisionCategoryBits(bits, std::string());
}


void JJB2Node::clrCollisionCategoryBits(uint16 bits,const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() ||(fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits &= ~bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


void JJB2Node::setCollisionCategoryBits(uint16 bits)
{
    this->setCollisionCategoryBits(bits, std::string());
}


void JJB2Node::setCollisionCategoryBits(uint16 bits,const std::string& fixtureId)
{
    b2Fixture *f = body->GetFixtureList();
    while(f)
    {
        if(!fixtureId.empty() || (fixtureId == *((std::string*)(f->GetUserData()))))
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits = bits;
            f->SetFilterData(filter);
        }
        f = f->GetNext();
    }
}


int JJB2Node::getObjectTag()
{
    return objectTag;
}


void JJB2Node::setObjectTag(int tag)
{
    objectTag = tag;
}


void JJB2Node::setAngularVelocity(float32 v)
{
    body->SetAngularVelocity(v);
}


void JJB2Node::addEdgeFrom(b2Vec2 start, b2Vec2 end)
{
    b2EdgeShape edgeShape;
    edgeShape.Set(start, end);
    body->CreateFixture(&edgeShape,0);
}

#pragma mark
#pragma mark JJB2ContactProtocol
void JJB2Node::beginContactWithOtherObject(JJB2Contact* contact)
{
    
}

void JJB2Node::endContactWithOtherObject(JJB2Contact* contact)
{
    
}


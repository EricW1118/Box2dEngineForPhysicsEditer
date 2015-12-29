//
//  JJB2Sprite.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2Sprite.h"

bool JJB2Sprite::initWithDynamicBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite)
{
    Sprite* sNode = nullptr;
    if (isFrameSpite)
        sNode = Sprite::createWithSpriteFrameName(spriteFrameName);
    else
        sNode = Sprite::create(spriteFrameName);
    return JJB2Node::initWithDynamicBody(shape,sNode);
}


bool JJB2Sprite::initWithStaticBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite)
{
    Sprite* sNode = nullptr;
    if (isFrameSpite)
        sNode = Sprite::createWithSpriteFrameName(spriteFrameName);
    else
        sNode = Sprite::create(spriteFrameName);
    return JJB2Node::initWithStaticBody(shape,sNode);
}


bool JJB2Sprite::initWithKinematicBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite)
{
    Sprite* sNode = nullptr;
    if (isFrameSpite)
        sNode = Sprite::createWithSpriteFrameName(spriteFrameName);
    else
        sNode = Sprite::create(spriteFrameName);
    return JJB2Node::initWithKinematicBody(shape,sNode);
}


JJB2Sprite* JJB2Sprite::spriteWithDynamicBody(const std::string& shape, const std::string& spriteFrameName)
{
    JJB2Sprite* s = new JJB2Sprite;
    s->JJB2Node::initWithDynamicBody(shape,Sprite::createWithSpriteFrameName(spriteFrameName));
    return s;
}

JJB2Sprite* JJB2Sprite::spriteWithStaticBody(const std::string& shape, const std::string& spriteFrameName)
{
    JJB2Sprite* s = new JJB2Sprite;
    s->JJB2Node::initWithStaticBody(shape,Sprite::createWithSpriteFrameName(spriteFrameName));
    return s;
}

JJB2Sprite* JJB2Sprite::spriteWithKinematicBody(const std::string& shape, const std::string& spriteFrameName)
{
    JJB2Sprite* s = new JJB2Sprite;
    s->JJB2Node::initWithKinematicBody(shape,Sprite::createWithSpriteFrameName(spriteFrameName));
    return s;
}

void JJB2Sprite::setDisplayFrame(SpriteFrame* newFrame)
{
    Sprite* s = dynamic_cast<Sprite*>(this->getCcNode());
    if (s)
    {
        s->setDisplayFrame(newFrame);
    }
}

void JJB2Sprite::setDisplayFrameNamed(const std::string& name)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    if (frame)
    {
        this->setDisplayFrame(frame);
    }
}

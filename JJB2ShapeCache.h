//
//  JJB2ShapeCache.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2ShapeCache__
#define __SmartTV__JJB2ShapeCache__

#include <string>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
USING_NS_CC;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef
{
public:
    FixtureDef()
    : next(0)
    {}
    
    ~FixtureDef()
    {
        delete next;
        delete fixture.shape;
    }
    
    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef:public Ref
{
public:
    FixtureDef *fixtures;
    Vec2 anchorPoint;
};


class JJB2ShapeCache
{
public:
    JJB2ShapeCache();
    virtual ~JJB2ShapeCache();
    static JJB2ShapeCache* shareInstance();
    void addShapesWithFile(const std::string& plist);
    void addFixturesToBody(b2Body* body,const std::string& shape);
    Vec2 anchorPointForShape(const std::string& shape);
    CC_SYNTHESIZE(float, ptmRatio_, ptmRatio);
protected:
    void init();
protected:
    Map<std::string, BodyDef*> shapeObjects_;
};

#endif /* defined(__SmartTV__JJB2ShapeCache__) */

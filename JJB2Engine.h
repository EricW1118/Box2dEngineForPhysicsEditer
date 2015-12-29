//
//  JJB2Engine.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2Engine__
#define __SmartTV__JJB2Engine__

#include "Box2D/Box2D.h"
#include "cocos2d.h"


extern float PTM_RATIO;

class JJB2Node;
class JJB2WorldContractListener;

typedef std::function<void(JJB2Node*)> JJB2NodeCallBack;


inline b2Vec2 b2Vec2FromVec2(const cocos2d::Vec2 &p)
{
    return b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
}

inline b2Vec2 b2Vec2FromCC(float x, float y)
{
    return b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
}

inline cocos2d::Vec2 Vec2Fromb2Vec2(const b2Vec2 &p)
{
    return cocos2d::Vec2(p.x * PTM_RATIO, p.y*PTM_RATIO);
}

class GB2WorldContactListener;

class JJB2Engine : public cocos2d::Ref
{
public:
    static JJB2Engine* sharedInstance();
    JJB2Engine();
    virtual ~JJB2Engine();
    
    void deleteWorld();
    void deleteAllObjects();
    void iterateObjectsWithBlock(JJB2NodeCallBack callback);
    
    void stopWorldUpdate();
    void startWorldUpdate();
    
    static void purcheEngine();

protected:
    void init();
    void step(float dt);
public:
    CC_SYNTHESIZE(b2World*, world, world);
    JJB2WorldContractListener *worldContactListener;
    bool m_isStop;
};

#endif /* defined(__SmartTV__JJB2Engine__) */

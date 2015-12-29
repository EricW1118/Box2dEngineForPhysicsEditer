//
//  JJB2DebugDrawLayer.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/13.
//
//

#ifndef __SmartTV__JJB2DebugDrawLayer__
#define __SmartTV__JJB2DebugDrawLayer__

#include "GLES-Render.h"
#include "cocos2d.h"

class JJB2DebugDrawLayer : public cocos2d::Layer
{
public:
    ~JJB2DebugDrawLayer();
    virtual bool init();
    
    virtual void draw(cocos2d::Renderer *renderer,
                      const cocos2d::Mat4 &transform,
                      bool transformUpdated) override;
    
    CREATE_FUNC(JJB2DebugDrawLayer);
    
protected:
    cocos2d::Mat4 _modelViewMV;
    void onDraw();
    cocos2d::CustomCommand _customCommand;
protected:
    b2World *world;                 //!< weak reference to the world
    GLESDebugDraw *debugDraw;
};

#endif /* defined(__SmartTV__JJB2DebugDrawLayer__) */

//
//  JJB2Sprite.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2Sprite__
#define __SmartTV__JJB2Sprite__

#include "JJB2Node.h"

class JJB2Sprite : public JJB2Node
{
public:
    
    bool initWithDynamicBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite = true);
    
                             
    bool initWithStaticBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite = true);
    
    
    bool initWithKinematicBody(const std::string& shape, const std::string& spriteFrameName, bool isFrameSpite = true);
    
    
    static JJB2Sprite* spriteWithDynamicBody(const std::string& shape, const std::string& spriteFrameName);
    

    static JJB2Sprite* spriteWithStaticBody(const std::string& shape, const std::string& spriteFrameName);
    
  
    static JJB2Sprite* spriteWithKinematicBody(const std::string& shape, const std::string& spriteFrameName);
    
    
    void setDisplayFrame(SpriteFrame* newFrame);
    
    
    void setDisplayFrameNamed(const std::string& shape);
};

#endif /* defined(__SmartTV__JJB2Sprite__) */

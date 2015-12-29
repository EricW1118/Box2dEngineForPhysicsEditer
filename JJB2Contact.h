//
//  JJB2Contact.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2Contact__
#define __SmartTV__JJB2Contact__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class JJB2Node;

class JJB2Contact : public cocos2d::Ref
{
public:
    static JJB2Contact* create(JJB2Node*object,
                               b2Fixture* ownFixture,
                               JJB2Node* otherObject,
                               b2Fixture* otherFixture,
                               b2Contact*contact);
    
    void init(JJB2Node*object,
              b2Fixture* ownFixture,
              JJB2Node* otherObject,
              b2Fixture* otherFixture,
              b2Contact*contact);
    
    void setEnabled(bool enabled);
    
    virtual ~JJB2Contact();
    
    b2Fixture*  getOwnFixture(){ return ownFixture;};
    b2Fixture*  getOtherFixture(){ return otherFixture;};
    b2Contact*  getBox2dContact(){ return box2dContact;};
    JJB2Node*  getOtherObject(){ return otherObject;};
    
protected:
    b2Fixture *ownFixture;   /**< the fixture that collided */
    JJB2Node *otherObject;    /**< the other object */
    b2Fixture *otherFixture; /**< the other object's fixture that collided */
    b2Contact *box2dContact; /**< the box2d contact structure */

};
#endif /* defined(__SmartTV__JJB2Contact__) */

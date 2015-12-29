//
//  JJB2WorldContractListener.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2WorldContractListener__
#define __SmartTV__JJB2WorldContractListener__

#include "Box2D/Box2D.h"


enum class JJB2ContactType
{
    EContactBegin,
    EContactEnd,
    EContactPresolve
};

class JJB2Contact;

class JJB2ContactProtocol
{
public:
    virtual void beginContactWithOtherObject(JJB2Contact* contact) = 0;
    virtual void endContactWithOtherObject(JJB2Contact* contact) = 0;
};

class JJB2WorldContractListener: public b2ContactListener
{
public:
    JJB2WorldContractListener();
    ~JJB2WorldContractListener();
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    void notifyObjects(b2Contact *contact, JJB2ContactType contactType);
protected:
};

#endif /* defined(__SmartTV__JJB2WorldContractListener__) */

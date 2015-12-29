//
//  JJB2WorldContractListener.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2WorldContractListener.h"
#include "JJB2Node.h"
#include "JJB2Contact.h"

JJB2WorldContractListener::JJB2WorldContractListener(){}


JJB2WorldContractListener::~JJB2WorldContractListener(){}


void JJB2WorldContractListener::BeginContact(b2Contact* contact)
{
    notifyObjects(contact, JJB2ContactType::EContactBegin);
}

void JJB2WorldContractListener::EndContact(b2Contact* contact)
{
    notifyObjects(contact, JJB2ContactType::EContactEnd);
}

void JJB2WorldContractListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(oldManifold);
    notifyObjects(contact, JJB2ContactType::EContactPresolve);
}

void JJB2WorldContractListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    B2_NOT_USED(contact);
    B2_NOT_USED(impulse);
}

void JJB2WorldContractListener::notifyObjects(b2Contact *contact, JJB2ContactType type)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    JJB2Node* a = (JJB2Node*)bodyA->GetUserData();
    JJB2Node* b = (JJB2Node*)bodyB->GetUserData();
    
    switch (type)
    {
        case JJB2ContactType::EContactBegin:
        {
            JJB2Contact* contactWithB = JJB2Contact::create(a, contact->GetFixtureA(), b, contact->GetFixtureB(), contact);
            a->beginContactWithOtherObject(contactWithB);
            
            JJB2Contact* contactWithA = JJB2Contact::create(b, contact->GetFixtureB(), a, contact->GetFixtureA(), contact);
            b->beginContactWithOtherObject(contactWithA);
            break;
        }
        case JJB2ContactType::EContactEnd:
        {
            JJB2Contact* contactWithB = JJB2Contact::create(a, contact->GetFixtureA(), b, contact->GetFixtureB(), contact);
            a->endContactWithOtherObject(contactWithB);
            
            JJB2Contact* contactWithA = JJB2Contact::create(b, contact->GetFixtureB(), a, contact->GetFixtureA(), contact);
            b->endContactWithOtherObject(contactWithA);
            break;
        }
        default:
            break;
    }
}
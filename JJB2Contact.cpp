//
//  JJB2Contact.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2Contact.h"
#include "JJB2Node.h"

JJB2Contact* JJB2Contact::create(JJB2Node*object,
                           b2Fixture* ownFixture,
                           JJB2Node* otherObject,
                           b2Fixture* otherFixture,
                           b2Contact*contact)
{
    JJB2Contact* c = new JJB2Contact;
    c->init(object, ownFixture, otherObject, otherFixture, contact);
    c->autorelease();
    return c;
}

void JJB2Contact::init(JJB2Node*object,
          b2Fixture* aOwnFixture,
          JJB2Node* aOtherObject,
          b2Fixture* aOtherFixture,
          b2Contact*contact)
{
    otherObject = aOtherObject;
    otherObject->retain();
    ownFixture = aOwnFixture;
    otherFixture = aOtherFixture;
    box2dContact = contact;
}

void JJB2Contact::setEnabled(bool enabled)
{
     box2dContact->SetEnabled(enabled);
}

JJB2Contact::~JJB2Contact()
{
    otherObject->release();
    otherObject = nullptr;
}
//
//  JJB2Node.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef __SmartTV__JJB2Node__
#define __SmartTV__JJB2Node__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "JJB2ShapeCache.h"
#include "JJB2Engine.h"
#include "JJB2WorldContractListener.h"
USING_NS_CC;

class JJB2Node: public Ref, public JJB2ContactProtocol
{

public:
	JJB2Node();
	virtual~JJB2Node();
public:
    /**
     * Inits the object with a CCNode but no physics object
     * @param node CCNode which represents the object
     * @return the object
     */
    bool initWithNode(Node* node);
    
    /**
     * Inits the object with a dynamic shape and node
     * @param shape name of the physics shape to use
     * @param node CCNode to use for this object
     * @return the object
     */
    bool initWithDynamicBody(const std::string& shape,Node* node);
    
    /**
     * Inits the object with a static shape and node
     * @param shape name of the physics shape to use
     * @param node CCNode to use for this object
     * @return the object
     */
    bool initWithStaticBody(const std::string& shape, Node*node);
    
    /**
     * Inits the object with a kinematic shape and node
     * @param shape name of the physics shape to use
     * @param node CCNode to use for this object
     * @return the object
     */
    bool initWithKinematicBody(const std::string& shape, Node*node);
    
    /**
     * Inits the object with a shape, body type and node
     * @param shape name of the physics shape to use
     * @param node CCNode to use for this object
     * @return the object
     */
    bool initWithShape(const std::string& shape, b2BodyType bodyType ,Node* node);
    
    /**
     * Adds a fixture to the body
     * @param fixtureDef fixture definition
     * @return the added fixture
     */
    b2Fixture* addFixture(b2FixtureDef* fixtureDef);
    
    /**
     * Starts the given action on the inner CCNode
     * Should only be used with actions which do not
     * move or scale / rotate the object
     * @param action action to run
     * @return action
     */
    Action* runAction(Action* action);
    
    /**
     * Stops all actions on the inner CCNode
     */
    void stopAllActions();
    
    /**
     * Stops the given action on the inner CCNode
     * @param action action to stop
     */
    void stopAction(Action*  action);
    
    /**
     * Sets the CCNode to visible/invisible
     */
    void setVisible(bool isVisible);
    
    /**
     * Sets the object's angle
     * @param angle angle to set
     */
    void setAngle(float angle);
    
    /**
     * Sets the position from pixel coordinates
     * @param p position to set
     */
    void setCcPosition(Vec2 p);
    
    /**
     * Scales the graphics (currently not the object!)
     * @param scale scale to set
     */
    void setScale(float scale);
    
    /**
     * Returns the object's position in pixel coordinates
     */
    const Vec2& ccPosition();
    
    /**
     * Delete the object, remove it from the parent scene
     */
    void deleteNow();
    
    /**
     * Returns true if the body is awake
     */
    bool isAwake();
    
    /**
     * Called by GB2Engine to update the shape's position
     * and rotation from the physics coordinates
     */
    void updateCCFromPhysics();
    
    /**
     * Replaces the current fixtures with the new shape
     * @param shapeName name of the shape to set
     */
    void setBodyShape(const std::string& shapeName);
    
    /**
     * Returns the object's mass
     * @return mass
     */
    float mass();
    
    /**
     * Returns the position of the object in physics coordinates
     * @return position
     */
    b2Vec2 physicsPosition();
    
    /**
     * Sets the physics position of the object
     * @param position position to set
     */
    void setPhysicsPosition(b2Vec2 position);
    
    /**
     * Returns the world center of the object
     * @return world center
     */
    b2Vec2 worldCenter();
    
    /**
     * Replaces the object's fixtures with the new shape
     * and sets the positon and body type to kinematic
     * @param shapeName name of the shape to set
     * @param pos position of the object
     */
    void setKinematicBody(const std::string& shapeName,b2Vec2 position);
    
    /**
     * Replaces the object's fixtures with the new shape
     * and sets the positon and body type to dynamic
     * @param shapeName name of the shape to set
     * @param pos position of the object
     */
    void setDynamicBody(const std::string& shapeName, b2Vec2 position);
    
    /**
     * Replaces the object's fixtures with the new shape
     * and sets the positon and body type to static
     * @param shapeName name of the shape to set
     * @param pos position of the object
     */
    void setStaticBody(const std::string& shapeName, b2Vec2 position);
    
    /**
     * Sets the body type of the object
     * b2_kinematicBody, b2_staticBody, b2_dynamicBody
     * @param bodyType
     */
    void setBodyType(b2BodyType bodyType);
    
    /**
     * Applies an impulse at the given point of the object
     * Use [self worldCenter] to apply the impulse to the
     * center of the object without setting the object
     * into a rotation
     * @param impulse impulse to apply
     * @param point point to apply the impulse to
     */
    void applyLinearImpulse(b2Vec2 impulse,b2Vec2 point);
    
    /**
     * Sets the linear velocity of the object
     * @param velocity velocity vector to set
     */
    void setLinearVelocity(b2Vec2 velocity);
    
    /**
     * Enables / disables rotation on the object
     * If called with YES the object can't rotate
     * @param fixedRotation
     */
    void setFixedRotation(bool fixedRotation);
    
    /**
     * Add damping
     * @param linearDamping daming value to set
     */
    void setLinearDamping(float linearDamping);
    
    /**
     * Add angular damping
     * @param angularDamping damping value
     */
    void setAngularDamping(float angularDamping);
    
    /**
     * Apply a force to the given point of the object
     * @param force force to apply
     * @param point point on the object to apply the force to
     */
    void applyForce(b2Vec2 force, b2Vec2 point);
    
    /**
     * Returns the angle of the object
     * @return angle
     */
    float angle();
    
    /**
     * Sets the position and rotation of the object
     * @param pos position to set
     * @param angle angle to set
     */
    void setTransform(b2Vec2 pos,float angle);
    
    /**
     * Returns true if the object is active (participates
     * in collition detection etc.
     */
    bool active();
    
    /**
     * Sets the object to active (or not)
     * If the object is inactive it will not participate in
     * collition detection
     */
    void setActive(bool isActive);
    
    /**
     * Returns true if the body is sleeping
     * That means was not hit by other objects for some time
     * @return true if object is awake
     */
    bool awake();
    
    /**
     * Returns the linear velocity of the object
     * @return linear velocity
     */
    b2Vec2 linearVelocity();
    
    /**
     * Sets the object to bullet mode and activates continuous collision
     * detection for the object
     */
    void setBullet(bool bulletFlag);
    
    /**
     * Destroys the physics body of the object
     */
    void destroyBody();
    
    /**
     * Returns the object's width in meters taken from the
     * sprite's size. If the sprite has transparent borders
     * this might differ from the object's real size
     */
    float widthInM();
    
    /**
     * Clears mask bits on the object's fixtures
     * Bits to clear must be set to 1
     * @param bits bits to clear
     */
     void clrCollisionMaskBits(uint16 bits);
    
    /**
     * Clears mask bits on the object's fixtures
     * Bits to clear must be set to 1
     * @param bits bits to clear
     * @param forId only change the bits for the given fixtureID
     */
     void clrCollisionMaskBits(uint16 bits,const std::string& fixtureId);
    
    /**
     * Adds mask bits on the object's fixtures
     * Bits to set must be set to 1
     * @param bits bits to set
     */
     void addCollisionMaskBits(uint16 bits);
    
    /**
     * Adds mask bits on the object's fixtures
     * Bits to set must be set to 1
     * @param bits bits to set
     * @param forId only change the bits for the given fixtureID
     */
     void addCollisionMaskBits(uint16 bits,const std::string& fixtureId);
    
    /**
     * Sets the mask bits to the given value
     * @param bits bits
     */
     void setCollisionMaskBits(uint16 bits);
    
    /**
     * Sets the mask bits to the given value
     * @param bits bits
     * @param forId only change the bits for the given fixtureID
     */
     void setCollisionMaskBits(uint16 bits, const std::string& fixtureId);
    
    /**
     * Add bits to the collision category
     * @param bits bits to set
     */
     void addCollisionCategoryBits(uint16 bits);
    
    /**
     * Add bits to the collision category
     * @param bits bits to set
     * @param forId only change the bits for the given fixtureID
     */
     void addCollisionCategoryBits(uint16 bits,const std::string& fixtureId);
    
    /**
     * Clr bits on the collition category
     * Bits to clear must be set to 1
     * @param bits to clr
     */
     void clrCollisionCategoryBits(uint16 bits);
    
    /**
     * Clr bits on the collition category
     * Bits to clear must be set to 1
     * @param bits to clr
     * @param forId only change the bits for the given fixtureID
     */
     void clrCollisionCategoryBits(uint16 bits,const std::string& fixtureId);
    
    /**
     * Sets the category bits to the given value
     * @param bits bits to set
     */
     void setCollisionCategoryBits(uint16 bits);
    
    /**
     * Sets the category bits to the given value
     * @param bits bits to set
     * @param forId only change the bits for the given fixtureID
     */
     void setCollisionCategoryBits(uint16 bits,const std::string& fixtureId);
    
    /**
     * Returns the object's tag
     * @return tag of the object
     */
     int getObjectTag();
    
    /**
     * Tag the object with an integer value
     * @param tag tag value to set
     */
     void setObjectTag(int tag);
    
    
    /**
     * Sets the object's angular velocity
     * @param v velocity to set
     */
     void setAngularVelocity(float32 v);
    
    /**
     * Adds an edge to the fixture
     */
     void addEdgeFrom(b2Vec2 start, b2Vec2 end);
    
    
public://JJB2ContactProtocol
    virtual void beginContactWithOtherObject(JJB2Contact* contact);
    virtual void endContactWithOtherObject(JJB2Contact* contact);
    
public:

    inline bool getIsUpdatePos()
    {
        return isUpdatePos;
    };

	inline void setIsUpdatePos(bool update)
	{
		isUpdatePos = update;
	};
    
    CC_SYNTHESIZE(bool, deleteLater, DeleteLater); //!< flag to delete the object on update phase
    CC_SYNTHESIZE_RETAIN(Node*, ccNode, CcNode); //!< reference to the ccNode, retained
    b2Body* getBody(){return body;};
    

protected:
    void setBody(const std::string& shapeName,b2BodyType bodyType, b2Vec2 pos);
    
protected:
    b2Body* body;       //!< pointer to the box2d's body
    b2World *world;     //!< pointer to the world object
    int objectTag;      //!< tag might be used to query an object
    bool isUpdatePos;
};

#endif /* defined(__SmartTV__JJB2Node__) */

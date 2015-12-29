//
//  JJB2ShapeCache.cpp
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#include "JJB2ShapeCache.h"

std::vector<std::string> split(std::string str,std::string pattern)
{
     std::string::size_type pos;
     std::vector<std::string> result;
     str+=pattern;//扩展字符串以方便操作
     size_t size=str.size();
     for(unsigned long i=0; i<size; i++)
     {
         pos=str.find(pattern,i);
         if(pos<size)
         {
             std::string s=str.substr(i,pos-i);
             result.push_back(s);
             i=pos+pattern.size()-1;
         }
     }
     return result;
}

static Vec2 Vec2FromString_(const std::string& str)
{
    std::string theString = str;
    auto pos = theString.find("{");
    if (pos != std::string::npos)
    {
        theString.erase(pos,1);
    }
    
    pos = theString.find("}");
    if (pos != std::string::npos)
    {
        theString.erase(pos,1);
    }
    auto array = split(theString,",");
    
    CCLOG("array size = %ld",array.size());
    
    if (array.size() >= 2)
    {
        return Vec2(atof(array.at(0).c_str()), atof(array.at(1).c_str()));
    }
    else
    {
        assert("----------can't convert to Vec2 from string!! ");
        return Vec2::ZERO;
    }
}

JJB2ShapeCache* JJB2ShapeCache::shareInstance()
{
    static JJB2ShapeCache* instace = 0;
    if (!instace)
    {
        instace = new JJB2ShapeCache;
        instace->init();
    }
    return instace;
}

void JJB2ShapeCache::init()
{
    
}

JJB2ShapeCache::JJB2ShapeCache()
{
    
}

JJB2ShapeCache::~JJB2ShapeCache()
{
    
}


void JJB2ShapeCache::addShapesWithFile(const std::string& plist)
{
    std::string path = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dictionary = FileUtils::getInstance()->getValueMapFromFile(path);
    ValueMap metadataDict =  (dictionary.find("metadata")->second).asValueMap();
    
    int format =  (metadataDict.find("format")->second).asInt();
    ptmRatio_ =   (metadataDict.find("ptm_ratio")->second).asFloat();
    
    CCASSERT(format == 1, "Format not supported");
    ValueMap bodyDict =  (dictionary.find("bodies")->second).asValueMap();
    b2Vec2 vertices[b2_maxPolygonVertices];
    
    for(ValueMap::iterator iter = bodyDict.begin(); iter != bodyDict.end(); iter++)
    {
        ValueMap bodyData = (iter->second).asValueMap();
        // create body object
        BodyDef *bodyDef =  new BodyDef;
        bodyDef->autorelease();
        bodyDef->anchorPoint =  Vec2FromString_((bodyData.find("anchorpoint")->second).asString());
        ValueVector fixtureList = (bodyData.find("fixtures")->second).asValueVector();
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);
        for(Value fixtureValue : fixtureList)
        {
            ValueMap fixtureData = fixtureValue.asValueMap();
            b2FixtureDef basicData;
            basicData.filter.categoryBits =  (fixtureData.find("filter_categoryBits")->second).asInt();
            basicData.filter.maskBits = (fixtureData.find("filter_maskBits")->second).asInt();
            basicData.filter.groupIndex =   (fixtureData.find("filter_groupIndex")->second).asInt();
            basicData.friction =  (fixtureData.find("friction")->second).asFloat();
            basicData.density = (fixtureData.find("density")->second).asFloat();
            basicData.restitution =  (fixtureData.find("restitution")->second).asFloat();
            basicData.isSensor = (fixtureData.find("isSensor")->second).asBool();
            basicData.userData = new std::string((fixtureData.find("id")->second).asString());
            
            int callbackData = 0;//(fixtureData.find("userdataCbValue")->second).asInt();
            
            std::string fixtureType =(fixtureData.find("fixture_type")->second).asString();
            // read polygon fixtures. One convave fixture may consist of several convex polygons
            if(fixtureType == "POLYGON"/*[fixtureType isEqual:@"POLYGON"]*/)
            {
                ValueVector polygonsArray = (fixtureData.find("polygons")->second).asValueVector();
                
                for(Value polygonValue : polygonsArray)
                {
                    ValueVector polygonArray = polygonValue.asValueVector();
                    FixtureDef* fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
                    b2PolygonShape* polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
                    assert(polygonArray.size()<= b2_maxPolygonVertices);
                    for(Value pointValue : polygonArray)
                    {
                        std::string pointString = pointValue.asString();
                        Vec2 offset = Vec2FromString_(pointString);
                        vertices[vindex].x = (offset.x / ptmRatio_) ;
                        vertices[vindex].y = (offset.y / ptmRatio_) ;
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
                }
            }
            else if(fixtureType == "CIRCLE"/*[fixtureType isEqual:@"CIRCLE"]*/)
            {
                FixtureDef* fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
                //NSDictionary *circleData = [fixtureData objectForKey:@"circle"];
                ValueMap circleData = (fixtureData.find("circle")->second).asValueMap();
                
                b2CircleShape *circleShape = new b2CircleShape();
                circleShape->m_radius = (circleData.find("radius")->second).asFloat() / ptmRatio_;
                Vec2 p = Vec2FromString_( (circleData.find("position")->second).asString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio_, p.y / ptmRatio_);
                fix->fixture.shape = circleShape;
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);
            }
            else
            {
                // unknown type
                assert(0);
            }
        }
        // add the body element to the hash
        shapeObjects_.insert(iter->first, bodyDef);
    }
}

void JJB2ShapeCache::addFixturesToBody(b2Body* body,const std::string& shape)
{
    auto iter = shapeObjects_.find(shape);
    
    if (iter != shapeObjects_.end())
    {
        BodyDef *so = iter->second;
        FixtureDef *fix = so->fixtures;
        while(fix)
        {
            body->CreateFixture(&fix->fixture);
            fix = fix->next;
        }
    }
}

Vec2 JJB2ShapeCache::anchorPointForShape(const std::string& shape)
{
    auto iter = shapeObjects_.find(shape);
    
    if (iter != shapeObjects_.end())
    {
        BodyDef *bd = iter->second;
        return bd->anchorPoint;
    }
    else
    {
        assert(nullptr);
    }
}


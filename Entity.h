

#ifndef __ENTIIY_SCENE_H__
#define __ENTIIY_SCENE_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Entity
{
public: 
    Sprite* sprite;

    Entity();
    Entity(const string& file);
    ~Entity();

    PhysicsBody* body;

    enum Enemies {
        Raptor,
        Savenger
    };
};

#endif // __Entity_SCENE_H__

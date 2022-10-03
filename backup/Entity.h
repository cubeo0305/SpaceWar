#ifndef __ENTIIY_SCENE_H__
#define __ENTIIY_SCENE_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Entity
{
public: 
    Sprite* sprite;
    int healthEnemy;
    float maxHP;
    float hp;
    float damage;

    Entity();
    Entity(const string& file);
    ~Entity();
    enum Enemies {
        Raptor,
        Savenger
    };
    
    virtual void setMaxHP(float hp);
    virtual float getMaxHP();
    
    virtual void setHealthEnemy(float hp);
    virtual int getHealthEnemy();
    
    virtual float getDamage();
    virtual void setDamage(float damage);
    virtual void TakeDamage(float damage);
};

#endif // __Entity_SCENE_H__

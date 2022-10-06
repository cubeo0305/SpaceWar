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

    virtual void destroy();

    enum Enemies {
        Raptor,
        Savenger
    };
    Sprite* getSprite();

    void init();

    void setMaxHP(float hp);
    float getMaxHP();
    void setHP(float hp);
    float getHP();
    
    float getDamage();
    void setDamage(float damage);
    void TakeDamage(float damage);
};

#endif // __Entity_SCENE_H__

#ifndef __RAPTOR2_SCENE_H__
#define __RAPTOR2_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "BulletEnemy.h"

using namespace cocos2d;

class Raptor2 : public Enemy
{
public:
    static Raptor2* createRaptor2();
    virtual bool init();
    void update(float dt);
    
    float maxHP;

    BulletEnemy* bullet;

    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Sprite* raptor2;
    int soundshoot;
    int soundexplosion;
    
    PhysicsBody* body;
    void Shooting();
    //void EnemiesMove(bool isStart);
    void RaptorMove();

    int getHealthEnemy();
    void setHealthEnemy();

    CREATE_FUNC(Raptor2);
};

#endif // __HELLOWORLD_SCENE_H__

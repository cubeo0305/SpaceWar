#ifndef __RAPTOR1_SCENE_H__
#define __RAPTOR1_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "BulletEnemy.h"

using namespace cocos2d;

class Raptor1 : public Enemy
{
public:
    static Raptor1* createRaptor1();
    virtual bool init();
    void update(float dt);
    
    float maxHP;

    BulletEnemy* bullet;
    BulletEnemy* bullet1;
    BulletEnemy* bullet2;

    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Sprite* raptor1;
    int soundshoot;
    int soundexplosion;
    
    PhysicsBody* body;
    void Shooting();
    //void EnemiesMove(bool isStart);
    void RaptorMove();

    int getHealthEnemy();
    void setHealthEnemy();

    CREATE_FUNC(Raptor1);
};

#endif // __HELLOWORLD_SCENE_H__

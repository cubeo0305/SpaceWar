#ifndef __RAPTOR_SCENE_H__
#define __RAPTOR_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "BulletEnemy.h"

using namespace cocos2d;

class Raptor : public Enemy
{
public:
    static Raptor* createRaptor();
    virtual bool init();
    void update(float dt);
    
    float maxHP;

    BulletEnemy* bullet;

    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Sprite* raptor;
    int soundshoot;
    int soundexplosion;
    
    PhysicsBody* body;
    void Shooting();
    //void EnemiesMove(bool isStart);
    void RaptorMove();

    int getHealthEnemy();
    void setHealthEnemy();

    CREATE_FUNC(Raptor);
};

#endif // __HELLOWORLD_SCENE_H__

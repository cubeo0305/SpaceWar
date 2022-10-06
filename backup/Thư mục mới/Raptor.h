#ifndef __RAPTOR_SCENE_H__
#define __RAPTOR_SCENE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "BulletEnemy.h"

using namespace cocos2d;

class Raptor : public Node , public Entity
{
public:
    static Raptor* createRaptor();
    virtual bool init();
    void update(float dt);
        
    BulletEnemy* bullet;

    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Sprite* raptor;

    PhysicsBody* body;
    void Shooting();
    void EnemiesMove(bool isStart);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Raptor);
};

#endif // __HELLOWORLD_SCENE_H__

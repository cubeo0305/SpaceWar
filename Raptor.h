#ifndef __RAPTOR_SCENE_H__
#define __RAPTOR_SCENE_H__

#include "cocos2d.h"


using namespace cocos2d;

class Raptor : public Node
{
public:
    static Raptor* createRaptor();
    virtual bool init();
    void update(float dt);
        
    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Sprite* raptor;
    void Shooting();
    void SpawnEnemies();
    void EnemiesMove(bool isStart);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    PhysicsBody* body;
    PhysicsBody* bullet;
    // implement the "static create()" method manually
    CREATE_FUNC(Raptor);
};

#endif // __HELLOWORLD_SCENE_H__

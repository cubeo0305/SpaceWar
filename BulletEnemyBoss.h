#ifndef __BULLETENEMYBOSS_SCENE_H__
#define __BULLETENEMYBOSS_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class BulletEnemyBoss : public Node
{
public:
    static BulletEnemyBoss* createBullet();
    virtual bool init();
    void Physicbodys();
    void CreateBullet();

    PhysicsBody* body;
    PhysicsBody* body1;
    PhysicsBody* body2;
    cocos2d::Sprite* bullet;
    cocos2d::Sprite* bullet1;
    cocos2d::Sprite* bullet2;

    CREATE_FUNC(BulletEnemyBoss);
};

#endif // __BULLETPLAYER_SCENE_H__

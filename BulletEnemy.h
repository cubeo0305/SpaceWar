#ifndef __BULLETENEMY_SCENE_H__
#define __BULLETENEMY_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class BulletEnemy : public Node
{
public:
    static BulletEnemy* createBullet();
    virtual bool init();
        
    PhysicsBody* body;

    cocos2d::Sprite* bullet;

    CREATE_FUNC(BulletEnemy);
};

#endif // __BULLETPLAYER_SCENE_H__

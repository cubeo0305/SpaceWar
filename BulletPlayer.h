#ifndef __BULLETPLAYER_SCENE_H__
#define __BULLETPLAYER_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class BulletPlayer : public Node
{
public:
    static BulletPlayer* createBullet();
    virtual bool init();
        
    PhysicsBody* body;

    cocos2d::Sprite* bullet;

    CREATE_FUNC(BulletPlayer);
};

#endif // __BULLETPLAYER_SCENE_H__

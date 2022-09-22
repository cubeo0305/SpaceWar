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
        
    cocos2d::Sprite* raptor;
    void Shooting();
    void SpawnEnemies();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Raptor);
};

#endif // __HELLOWORLD_SCENE_H__

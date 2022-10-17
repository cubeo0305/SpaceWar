#ifndef __LOSESCENE_SCENE_H__
#define __LOSESCENE_SCENE_H__

#include "cocos2d.h"

class LoseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int _dmg);
    virtual bool init();
    void update(float dt);
    int sound;
    int soundLose;
    void initContactListener();
    void onMouseDown(cocos2d::Event* event);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    //int EnemyDie;
    CREATE_FUNC(LoseScene);
};

#endif // __LOSESCENE_SCENE_H__

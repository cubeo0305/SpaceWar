#ifndef __MAINMENUGAME_SCENE_H__
#define __MAINMENUGAME_SCENE_H__

#include "cocos2d.h"

class MainMenuGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt);
    
    int sound;
    int soundmenu;
    
    void initContactListener();
    void onMouseDown(cocos2d::Event* event);
    void initGame();
    void menuCloseCallback(cocos2d::Ref* pSender);
    //int EnemyDie;
    CREATE_FUNC(MainMenuGame);
};

#endif // __MAINMENUGAME_SCENE_H__

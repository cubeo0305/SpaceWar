#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int _score);

    virtual bool init();
    void update(float dt);

private:
    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* mySprite2;
    
    int sound;
    int soundWin;
    // When collision ended
    void onContactSeparate(cocos2d::PhysicsContact& contact);

    // Init contact listener
    void initContactListener();
    void onMouseDown(cocos2d::Event* event);

    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

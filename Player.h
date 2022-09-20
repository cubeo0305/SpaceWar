#ifndef __Player_SCENE_H__
#define __Player_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Player : public Node
{
public:
    static Player* createPlayer();
    void update(float dt);
    virtual bool init();

    cocos2d::Sprite* player;

    cocos2d::Vec2 direction;

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void Shooting();
    void setIsShooting(bool isShooting);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    bool isKeyDown = false;
    float speed;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Player);
};

#endif // __PLAYER_SCENE_H__

#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"
#include "BulletPlayer.h"

using namespace cocos2d;

class Player : public Node , public Entity
{
private:
    int heart;
    void initEventListener();
public:
    int getHeart();
    void setHeart(int heart);
    void takeDamage(float damage);

    static Player* createPlayer();
    BulletPlayer* bullet;
    void update(float dt);
    virtual bool init();
    cocos2d::Sprite* player;
    PhysicsBody* body;
    cocos2d::Vec2 direction;

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void Shooting();
    void setIsShooting(bool isShooting);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //Animation
    /*cocos2d::Animation* animation;
    Animation* createAnimation(string prefixName, int pFramesOrder, float deplay);
    void initAnimation();*/

    bool isKeyDown = false;
    float speed;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Player);
};

#endif // __PLAYER_SCENE_H__

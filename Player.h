#ifndef __Player_SCENE_H__
#define __Player_SCENE_H__

#include "cocos2d.h"
#include "BulletPlayer.h"

using namespace cocos2d;
using namespace std;

class Player : public Node 
{
private:
    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
public:
    static Player* createPlayer();
    BulletPlayer* bullet;
    void update(float dt);
    virtual bool init();
    
    float maxHP;
    int hp;
    int soundshoot;
    

    cocos2d::Sprite* player;
    PhysicsBody* body;
    cocos2d::Vec2 direction;

    void MoveCheck();
    void bodys();

    void Shooting();
    void initLis();
    void RunAnimation();
    void setIsShooting(bool isShooting);
    
    bool isKeyDown = false;
    float speed;

    //setHeal
    void setHealPlayer();
    int getHealPlayer();
    void setHealth();

    //Animation
    void initAnimation();
    cocos2d::Animation* createAnimation(string prefixName, int pFramesOrder, float delay);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Player);
};

#endif // __PLAYER_SCENE_H__

#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Raptor.h"
#include "Savenger.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Health.h"
#include "Enemy.h"

class GameScene : public cocos2d::Scene
{
private:
    PhysicsWorld* world;
    void setPhysicsWorld(PhysicsWorld* _world)
    {
        world = _world;
    }
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    float Wave;

    Player* player;
    Raptor* raptor;
    Savenger* savenger;
    Asteroid* asteroid;
    Boss* boss;
    Health* healing;
    Node* playerInfo;
    Node* damgeNode;

    int damage;

    cocos2d::Sprite* planet;
    cocos2d::Sprite* clouds;
    void InitGame();
    void ActionPlane();
    void update(float dt);
    bool onContactBegin(PhysicsContact& contact);
    void WaveEnemies();
    void initContactListener();
    void PlayerDie();
    void BackGround();
    void HealthPlayer();
    void initPlayerUI();
    void updatePlayerUI();
    void cloud();

    void SpawnEnemies();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__

#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Raptor.h"
#include "Savenger.h"


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
    
    Player* player;
    Raptor* raptor;
    Savenger* savenger;

    bool onContactBegin(PhysicsContact& contact);
    //void onContactSeparate(PhysicsContact& contact);
    void initContactListener();

    void SpawnEnemies();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__

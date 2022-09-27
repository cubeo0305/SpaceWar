#ifndef __GAMEMANAGER_SCENE_H__
#define __GAMEMANAGER_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Raptor.h"
#include "Savenger.h"
#include "Entity.h"

class GameManager : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    Player* player;
    Raptor* raptor;
    Savenger* savenger;
    
    void SpawnEnemies();
    void Start();
    CREATE_FUNC(GameManager);
};

#endif // __GameManager_SCENE_H__

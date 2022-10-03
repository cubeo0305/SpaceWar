#ifndef __GAMEMANAGER_SCENE_H__
#define __GAMEMANAGER_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Raptor.h"
#include "Savenger.h"
#include "Entity.h"
#include <vector>

static class GameManager 
{
public:
    GameManager();
    ~GameManager();
    virtual bool init();
    static Scene* world;
    static std::vector<Entity*> enemies;
    static std::vector<Entity*> entities;

    Player* player;
    Raptor* raptor;
    Savenger* savenger;

    static void setWorld(Scene* world);
    static Scene* getWorld();
    void SpawnEnemies();
    void Start();

    static void addEntity(Entity* entity);
    static Entity* findEntity(Sprite* sprite);
    static void destroyEntity(Entity* entity);

};

#endif // __GameManager_SCENE_H__

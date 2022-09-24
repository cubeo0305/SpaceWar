#ifndef __GameManager_SCENE_H__
#define __GameManager_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

static class GameManager 
{
private:
public:
	static GameManager* createGameManager();
	virtual bool init();

	GameManager();
	~GameManager();
   
	static void Start();
	static void SpawnEnemies();
};

#endif // __GameManager_SCENE_H__

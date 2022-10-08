#ifndef __ENEMY_SCENE_H__
#define __ENEMY_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Enemy : public Node
{
public:
	virtual int getHealthEnemy() = 0;
	virtual void setHealthEnemy() = 0;
	
protected:
	int healthEnemy;
};

#endif // __HELLOWORLD_SCENE_H__

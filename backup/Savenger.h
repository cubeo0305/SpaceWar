#ifndef __Savenger_SCENE_H__
#define __Savenger_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class Savenger : public Enemy
{
private:
public:
	static Savenger* createSavenger();
	virtual bool init();
	
	float maxHP;

	PhysicsBody* body;
	cocos2d::Sprite* savenger;
	void AvenMove();
	void update(float dt);

	int getHealthEnemy();
	void setHealthEnemy();
	
	void EntityDie();

    CREATE_FUNC(Savenger);
};

#endif // __Savenger_SCENE_H__
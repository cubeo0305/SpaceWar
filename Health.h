#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "Enemy.h"
#include "Count.h"

using namespace cocos2d;

class Health : public Node
{
private:
public:
	static Health* createHealth();
	virtual bool init();

	PhysicsBody* body;
	
	cocos2d::Sprite* health;
	void AvenMove();
	void update(float dt);

    CREATE_FUNC(Health);
};

#endif // __AsteroidE_H__

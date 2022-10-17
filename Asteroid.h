#ifndef __Asteroid_H__
#define __Asteroid_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Count.h"

using namespace cocos2d;

class Asteroid : public Enemy
{
private:
public:
	static Asteroid* createAsteroid();
	virtual bool init();

	PhysicsBody* body;
	float maxHP;
	cocos2d::Sprite* asteroid;
    int sound;
	void AvenMove();
	void update(float dt);

	int getHealthEnemy();
	void setHealthEnemy();

    CREATE_FUNC(Asteroid);
};

#endif // __AsteroidE_H__

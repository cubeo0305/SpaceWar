#ifndef __Asteroid_H__
#define __Asteroid_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Asteroid : public Node , public Entity
{
private:
public:
	static Asteroid* createAsteroid();
	virtual bool init();

	PhysicsBody* body;
	cocos2d::Sprite* asteroid;
	void AvenMove();
	void update(float dt);

    CREATE_FUNC(Asteroid);
};

#endif // __AsteroidE_H__

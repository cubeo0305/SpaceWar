#ifndef __Boss_H__
#define __Boss_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "Enemy.h"
#include "BulletEnemy.h"
#include "Player.h"

using namespace cocos2d;

class Boss : public Enemy
{
private:
public:
	static Boss* createAsteroid();
	virtual bool init();

	PhysicsBody* body;
	BulletEnemy* bullet;
	Player* player;
	

	float maxHP;
	cocos2d::Sprite* boss;

	void AvenMove(bool isStart);
	void initLis();
	void Shooting();
	void update(float dt);

	int getHealthEnemy();
	void setHealthEnemy();

    CREATE_FUNC(Boss);
};

#endif // __AsteroidE_H__

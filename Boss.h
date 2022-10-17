#ifndef __Boss_H__
#define __Boss_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "BulletEnemyBoss.h"
#include "Player.h"


using namespace cocos2d;

class Boss : public Node
{
private:
public:
	static Boss* createAsteroid();
	virtual bool init();

	PhysicsBody* body;
	BulletEnemyBoss* bullet;
	Player* player;

	float maxHP;
    int sound;
    int soundshoot;
	int hp;
	cocos2d::Sprite* boss;
	cocos2d::Sprite* bossgun;

	void AvenMove(bool isStart);
	void initLis();
	void Shooting();
	void GunLook();
	void update(float dt);

	int getHealthBoss();
	void setHealthBoss();

    CREATE_FUNC(Boss);
};

#endif // __AsteroidE_H__

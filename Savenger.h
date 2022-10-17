#ifndef __Savenger_SCENE_H__
#define __Savenger_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;
using namespace std;

class Savenger : public Enemy
{
private:
public:
	static Savenger* createSavenger();
	virtual bool init();
	
	float maxHP;
    int soundexplosion;
	PhysicsBody* body;
	cocos2d::Sprite* savenger;
	void AvenMove();
	void update(float dt);

	int getHealthEnemy();
	void setHealthEnemy();

    CREATE_FUNC(Savenger);
};

#endif // __Savenger_SCENE_H__

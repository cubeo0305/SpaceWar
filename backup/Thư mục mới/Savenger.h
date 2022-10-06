#ifndef __Savenger_H__
#define __Savenger_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Savenger : public Node , public Entity
{
private:
public:
	static Savenger* createSavenger();
	virtual bool init();

	PhysicsBody* body;
	cocos2d::Sprite* savenger;
	void AvenMove();
	void update(float dt);
    CREATE_FUNC(Savenger);
};

#endif // __Savenger_SCENE_H__

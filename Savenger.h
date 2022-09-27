#ifndef __Savenger_SCENE_H__
#define __Savenger_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Savenger : public Node
{
private:
public:
	static Savenger* createSavenger();
	virtual bool init();
	cocos2d::Sprite* savenger;
	PhysicsBody* body;
	void AvenMove();
	void update(float dt);
   
    CREATE_FUNC(Savenger);
};

#endif // __Savenger_SCENE_H__

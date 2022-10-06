#ifndef __Count_H__
#define __Count_H__

#include "cocos2d.h"

using namespace cocos2d;

class Count 
{
public:
	virtual void EnemyDie() = 0;
	float count;
};

#endif // __Count_H__

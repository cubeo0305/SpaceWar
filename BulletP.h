#ifndef __BULLETP_SCENE_H__
#define __BULLETP_SCENE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Constant.h"

USING_NS_CC;

class BulletP : public Entity
{
public:
    BulletP(ContactType contactType);
    ~BulletP();
    
    bool init();

};

#endif // __BULLETP_H__

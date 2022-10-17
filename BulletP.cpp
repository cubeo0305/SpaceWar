#include "BulletP.h"

USING_NS_CC;

BulletP::BulletP(ContactType contactType):Entity("Bullet.png")
{
    this->sprite->setTag((int)contactType);
    
    this->body->setContactTestBitmask(PLAYER_BULLET_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(PLAYER_BULLET_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(PLAYER_BULLET_COLLISION_BITMASK);
    
    this->init();
}

BulletP::~BulletP()
{
    
}

bool BulletP::init()
{
//    auto onBottom = MoveBy::create(1, Vec2(0, 700));
//    auto cleanUp = CallFunc::create([=]() {
//        this->sprite->removeFromParentAndCleanup(true);
//        });
//    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
//    this->sprite->runAction(sequence);
    
    return true;
}


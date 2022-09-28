#include "BulletPlayer.h"
#include "Constant.h"
USING_NS_CC;

BulletPlayer* BulletPlayer::createBullet()
{
    return BulletPlayer::create();
}
bool BulletPlayer::init()
{
    if (!Node::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Sprite Bullet & Action
    this->bullet = Sprite::create("Bullet.png");
    this->bullet->setContentSize(Size(15, 15));
    addChild(this->bullet);

    auto onBottom = MoveBy::create(1, Vec2(0, 700));
    auto cleanUp = CallFunc::create([=]() {
        this->bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    this->bullet->runAction(sequence);

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->bullet->getContentSize());
    this->body->setDynamic(false);
    this->addComponent(this->body);

    this->body->setContactTestBitmask(PLAYER_BULLET_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(PLAYER_BULLET_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(PLAYER_BULLET_COLLISION_BITMASK);

    return true;
}


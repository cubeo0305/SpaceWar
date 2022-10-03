#include "BulletPlayer.h"
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
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(15);
    this->bullet->addComponent(this->body);
    return true;
}


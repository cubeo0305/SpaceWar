#include "BulletEnemy.h"
USING_NS_CC;

BulletEnemy* BulletEnemy::createBullet()
{
    return BulletEnemy::create();
}
bool BulletEnemy::init()
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
    this->bullet->setRotation(180);
    addChild(this->bullet);

    auto onBottom = MoveBy::create(1, Vec2(0, -700));
    auto cleanUp = CallFunc::create([=]() {
        this->bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    this->bullet->runAction(sequence);

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->bullet->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(25);
    this->bullet->addComponent(this->body);

    

    return true;
}


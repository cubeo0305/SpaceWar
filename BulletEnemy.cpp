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
    this->bulletenemy = Sprite::create("bpum1.png");
    this->bulletenemy->setScale(1.5);
    this->bulletenemy->setRotation(180);
    addChild(this->bulletenemy);

    auto onBottom = MoveBy::create(3, Vec2(0, -700));
    auto cleanUp = CallFunc::create([=]() {
        if (this->bulletenemy->getPositionY() <= 0)
        {
            this->bulletenemy->removeFromParentAndCleanup(true);
        }
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    this->bulletenemy->runAction(sequence);

    //PhysicsBody
    this->body = PhysicsBody::createCircle(
        this->bulletenemy->getContentSize().width/4);
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(25);
    this->bulletenemy->addComponent(this->body);

    return true;
}


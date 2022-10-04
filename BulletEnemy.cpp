#include "BulletEnemy.h"
#include "Constant.h"
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
    this->bullet = Sprite::create("bpum1.png");
    //this->bullet->setContentSize(Size(15, 15));
    this->bullet->setScale(1);
    this->bullet->setRotation(180);
    addChild(this->bullet);

    auto onBottom = MoveBy::create(2, Vec2(0, -700));
    auto cleanUp = CallFunc::create([=]() {
        this->bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    this->bullet->runAction(sequence);

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->bullet->getContentSize());
    this->body->setDynamic(false);
    this->bullet->addComponent(this->body);

    this->body->setContactTestBitmask(ENEMY_BULLET_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(ENEMY_BULLET_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(ENEMY_BULLET_COLLISION_BITMASK);

    return true;
}


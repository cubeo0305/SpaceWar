#include "BulletEnemyBoss.h"
USING_NS_CC;

BulletEnemyBoss* BulletEnemyBoss::createBullet()
{
    return BulletEnemyBoss::create();
}
bool BulletEnemyBoss::init()
{
    if (!Node::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->CreateBullet();
    this->Physicbodys();  
    return true;
}
void BulletEnemyBoss::CreateBullet()
{
    //Sprite Bullet & Action 1
    this->bullet = Sprite::create("bpum2.png");
    this->bullet->setScale(1.5);
    this->bullet->setRotation(180);
    addChild(this->bullet);
    auto onBottom = MoveBy::create(4, Vec2(250, 800));
    auto cleanUp = CallFunc::create([=]() {
        if (this->bullet->getPositionY() <= 0)
        {
            this->bullet->removeFromParentAndCleanup(true);
        }
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    this->bullet->runAction(sequence);

    //Sprite Bullet & Action 2
    this->bullet1 = Sprite::create("bpum2.png");
    this->bullet1->setScale(1.5);
    this->bullet1->setRotation(180);
    addChild(this->bullet1);
    auto onBottom1 = MoveBy::create(4, Vec2(0, 800));
    auto cleanUp1 = CallFunc::create([=]() {
        if (this->bullet1->getPositionY() <= 0)
        {
            this->bullet1->removeFromParentAndCleanup(true);
        }
        });
    auto sequence1 = Sequence::create(onBottom1, cleanUp1, nullptr);
    this->bullet1->runAction(sequence1);
    //Sprite Bullet & Action 2
    this->bullet2 = Sprite::create("bpum2.png");
    this->bullet2->setScale(1.5);
    this->bullet2->setRotation(180);
    addChild(bullet2);
    auto onBottom2 = MoveBy::create(4, Vec2(-250, 800));
    auto cleanUp2 = CallFunc::create([=]() {
        if (this->bullet2->getPositionY() <= 0)
        {
            this->bullet2->removeFromParentAndCleanup(true);
        }
        });
    auto sequence2 = Sequence::create(onBottom2, cleanUp2, nullptr);
    this->bullet2->runAction(sequence2);
}
void BulletEnemyBoss::Physicbodys()
{
    //PhysicsBody
    this->body = PhysicsBody::createCircle(this->bullet->getContentSize().width / 4);
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(25);
    this->bullet->addComponent(this->body);

    this->body1 = PhysicsBody::createCircle(this->bullet1->getContentSize().width / 4);
    this->body1->setDynamic(false);
    this->body1->setContactTestBitmask(true);
    this->body1->setCollisionBitmask(25);
    this->bullet1->addComponent(this->body1);

    this->body2 = PhysicsBody::createCircle(this->bullet2->getContentSize().width / 4);
    this->body2->setDynamic(false);
    this->body2->setContactTestBitmask(true);
    this->body2->setCollisionBitmask(25);
    this->bullet2->addComponent(this->body2);
}

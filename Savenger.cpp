#include "Savenger.h"
USING_NS_CC;


Savenger* Savenger::createSavenger()
{
    return Savenger::create();
}
bool Savenger::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->maxHP = 100;
    this->healthEnemy = this->maxHP;

    this->savenger = Sprite::create("Gunboss.png");
    this->savenger->setRotation(180);
    this->savenger->setPosition(Vec2(random(50, 550), 850));
    this->savenger->setScale(2.5);
    addChild(this->savenger);

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->savenger->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(20);
    this->savenger->addComponent(this->body);

    this->scheduleUpdate();
    this->AvenMove();
    

    return true;
}
void Savenger::update(float dt)
{

}
int Savenger::getHealthEnemy()
{
    return this->maxHP;
}
void Savenger::setHealthEnemy()
{
    this->healthEnemy -= 25;
    if (this->healthEnemy <= 0)
    {
        this->savenger->removeFromParentAndCleanup(true);
    }
}
void Savenger::AvenMove()
{
    /*auto Point1 = MoveTo::create(1, Vec2(590, 650));
    auto Point2 = MoveTo::create(1, Vec2(390, 650));
    auto Point3 = MoveTo::create(1, Vec2(190, 650));
    auto Point4 = MoveTo::create(1, Vec2(10, 650));
 
    auto sequen = Sequence::create(Point1, Point2, Point3, Point4, Point3, Point2, nullptr);
    this->savenger->runAction(sequen);*/

    auto moveBy = MoveBy::create(8, Vec2(0, -1000));
    this->savenger->runAction(moveBy);

    if (this->savenger->getPositionY() <= -20)
    {
        this->savenger->removeFromParentAndCleanup(true);
    }

}

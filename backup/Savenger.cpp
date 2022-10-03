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

    this->maxHP = 1;
    this->healthEnemy = this->maxHP;

    this->savenger = Sprite::create("Raptor.png");
    this->savenger->setRotation(180);
    addChild(this->savenger);

    //this->savenger->setPosition(Vec2(-15, 650));
    this->savenger->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    /*this->schedule([&](float dt)
        {
            this->AvenMove();
        }, 6, "Movement");*/

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->savenger->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(20);
    this->savenger->addComponent(this->body);

    this->scheduleUpdate();

    return true;
}

void Savenger::update(float dt)
{
    this->EntityDie();
}
int Savenger::getHealthEnemy()
{
    return this->maxHP;
}
void Savenger::setHealthEnemy()
{
    this->healthEnemy -= 25;
}
void Savenger::AvenMove()
{
    auto Point1 = MoveTo::create(1, Vec2(590, 650));
    auto Point2 = MoveTo::create(1, Vec2(390, 650));
    auto Point3 = MoveTo::create(1, Vec2(190, 650));
    auto Point4 = MoveTo::create(1, Vec2(10, 650));
 
    auto sequen = Sequence::create(Point1, Point2, Point3, Point4, Point3, Point2, nullptr);
    this->savenger->runAction(sequen);

}
void Savenger::EntityDie()
{
    if (this->healthEnemy <= 0)
    {
        auto newPos = Vec2(-10, -10);
        this->savenger->setPosition(newPos);
        this->savenger->stopAllActions();
        this->savenger->unschedule("Movement");
    }
}
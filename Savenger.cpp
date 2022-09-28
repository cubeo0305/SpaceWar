#include "Savenger.h"
#include "Constant.h"
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


    this->savenger = Sprite::create("Raptor.png");
    this->savenger->setRotation(180);
    addChild(this->savenger);
    //this->AvenMove();
    //this->savenger->stopAllActions();

    this->savenger->setPosition(Vec2(-15, 650));
    

    this->schedule([&](float dt)
        {
            this->AvenMove();
        }, 6, "Movement");

    //info Savenger
    this->maxHP = 100;
    this->hp = 100;
    this->damage = 100;
    //PhysicsBody
    this->body = PhysicsBody::createBox(this->savenger->getContentSize());
    this->body->setDynamic(false);
    this->savenger->addComponent(this->body);

    this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
    
    this->scheduleUpdate();

    return true;
}

void Savenger::update(float dt)
{
    this->EntityDie();
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
    if (this->hp < 0)
    {
        savenger->setPosition(Vec2(-100, -100));
        savenger->stopAllActions();
    }
}
#include "Asteroid.h"
#include "Constant.h"
USING_NS_CC;

Asteroid* Asteroid::createAsteroid()
{
    return Asteroid::create();
}
bool Asteroid::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    this->asteroid = Sprite::create("Asteroid.png");
    this->asteroid->setPosition(Vec2(random(50, 550), 850));
    this->asteroid->setScale(0.3);
    addChild(this->asteroid);

    //info Savenger
    this->maxHP = 1;
    this->hp = 1;
    this->damage = 100;

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->asteroid->getContentSize());
    this->body->setDynamic(false);
    this->asteroid->addComponent(this->body);

    this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
    
    this->scheduleUpdate();

    this->AvenMove();

    return true;
}

void Asteroid::update(float dt)
{
    
}
void Asteroid::AvenMove()
{
    auto moveBy = MoveBy::create(5, Vec2(0, -1500));
    this->asteroid->runAction(moveBy);
}

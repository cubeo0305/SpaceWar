#include "Health.h"
USING_NS_CC;

Health* Health::createHealth()
{
    return Health::create();
}
bool Health::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    health = Sprite::create("heart.png");
    health->setPosition(Vec2(random(50, 550), 850));
    health->setContentSize(Size(25, 25));
    addChild(health);

    //PhysicsBody
    this->body = PhysicsBody::createBox(health->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(2);
    health->addComponent(this->body);
        
    this->scheduleUpdate();
    this->AvenMove();

    return true;
}

void Health::update(float dt)
{
    
}
void Health::AvenMove()
{
    auto moveBy = MoveBy::create(6, Vec2(0, -1000));
    this->health->runAction(moveBy);

    if (this->health->getPositionY() <= -20)
    {
        this->health->removeFromParentAndCleanup(true);
    }
}

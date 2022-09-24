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

    this->savenger = Sprite::create("Ememy1.png");
    this->savenger->setRotation(180);
    addChild(this->savenger);
    this->AvenMove();
    return true;
}

void Savenger::update(float dt)
{

}
void Savenger::AvenMove()
{
    auto MoveDown = MoveBy::create(2, Vec2(0, -700));
    this->savenger->runAction(MoveDown);
}

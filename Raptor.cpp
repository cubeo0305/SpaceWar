#include "Raptor.h"

USING_NS_CC;

Raptor* Raptor::createRaptor()
{
    return Raptor::create();
}
bool Raptor::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->raptor = Sprite::create("Enemy4.png");
    addChild(this->raptor);
    this->raptor->setRotation(180);
    /*this->raptor->setPosition(Vec2(-10,400));

    auto moveto = MoveTo::create(2, Vec2(400, 600));
    this->raptor->runAction(moveto);*/


    this->raptor->schedule([&](float dt) {
        this->Shooting();
        }, 1.3 , "RaptorShooting");

    this->SpawnEnemies();


    return true;
}

void Raptor::update(float dt)
{
    
}
void Raptor::Shooting()
{
    auto bullet = Sprite::create("Bullet.png");
    bullet->setContentSize(Size(15, 20));
    bullet->setPosition(this->raptor->getPosition());
    bullet->setRotation(180);
    addChild(bullet);

    auto onBottom = MoveBy::create(1, Vec2(0, -700));
    auto cleanUp = CallFunc::create([=]() {
        bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onBottom, cleanUp, nullptr);
    bullet->runAction(sequence);
}
void Raptor::SpawnEnemies()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int positionMaxRand = 100;
    int positionMinRand = -100;
    int positionX = rand() % (positionMaxRand - positionMinRand + 1) + positionMinRand;
    int positionY = rand() % (positionMaxRand - positionMinRand + 1) + positionMinRand;

    Vec2 direction = Vec2(positionX, positionY);
    direction.normalize();
    const float padding = 100;
    Vec2 position = direction * (visibleSize.width / 2 + padding) + visibleSize / 2;

    this->raptor->setPosition(Vec2(position));
}

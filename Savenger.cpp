#include "Savenger.h"
#include "AudioEngine.h"

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

    this->savenger = Sprite::create("Y wing.png");
    this->savenger->setPosition(Vec2(random(50, 550), 850));
    this->savenger->setScale(2);
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
    soundexplosion = AudioEngine::play2d("sound/hit.wav");
    AudioEngine::setVolume(soundexplosion, 0.3);
    if (this->healthEnemy <= 0)
    {
        this->soundexplosion = AudioEngine::play2d("sound/die.wav");
        AudioEngine::setVolume(soundexplosion, 0.2);
        this->savenger->removeFromParentAndCleanup(true);
    }
}
void Savenger::AvenMove()
{
    auto moveBy = MoveBy::create(5, Vec2(0, -1000));
    this->savenger->runAction(moveBy);

    if (this->savenger->getPositionY() <= -20)
    {
        this->savenger->removeFromParentAndCleanup(true);
    }

}

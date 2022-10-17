#include "Raptor.h"
#include "AudioEngine.h"
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

    this->maxHP = 75;
    this->healthEnemy = this->maxHP;

    this->raptor = Sprite::create("ship1.png");
    this->raptor->setPosition(Vec2(random(50, 550), 850));
    this->raptor->setRotation(180);
    this->raptor->setScale(2);
    addChild(this->raptor);

    this->raptor->schedule([&](float dt) {
        this->Shooting();
        }, 1.3 , "RaptorShooting");

    this->scheduleUpdate();
    this->RaptorMove();

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->raptor->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(30);
    this->raptor->addComponent(this->body);

    return true;
}
void Raptor::update(float dt)
{
    
}
int Raptor::getHealthEnemy()
{
    return this->healthEnemy;
}
void Raptor::setHealthEnemy()
{
    this->healthEnemy -= 25;
    soundexplosion = AudioEngine::play2d("sound/hit.wav");
    AudioEngine::setVolume(soundexplosion, 0.3);
    if (this->healthEnemy <= 0)
    {
        this->raptor->removeFromParentAndCleanup(true);
        this->unschedule("RaptorShooting");
        this->soundexplosion = AudioEngine::play2d("sound/die.wav");
        AudioEngine::setVolume(soundexplosion, 0.2);

    }
}
void Raptor::Shooting()
{
    this->soundshoot = AudioEngine::play2d("sound/laser.wav");
    AudioEngine::setVolume(soundshoot, 0.5);
    
    bullet = BulletEnemy::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)raptor->getPositionX(),
        (int)raptor->getPositionY() - 20));
    
}
void Raptor::RaptorMove()
{
    auto moveBy = MoveBy::create(7, Vec2(0, -1000));
    this->raptor->runAction(moveBy);

    if (this->raptor->getPositionY() <= -20)
    {
        this->raptor->removeFromParentAndCleanup(true);
    }
}

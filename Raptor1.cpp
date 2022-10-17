#include "Raptor1.h"
#include "AudioEngine.h"
USING_NS_CC;

Raptor1* Raptor1::createRaptor1()
{
    return Raptor1::createRaptor1();
}
bool Raptor1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->maxHP = 80;
    this->healthEnemy = this->maxHP;

    this->raptor1 = Sprite::create("X wing.png");
    this->raptor1->setPosition(Vec2(random(50, 550), 850));
    this->raptor1->setScale(2.5);
    addChild(this->raptor1);

    this->raptor1->schedule([&](float dt) {
        this->Shooting();
        }, 2.3 , "RaptorShooting");

    this->scheduleUpdate();
    this->RaptorMove();

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->raptor1->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(31);
    this->raptor1->addComponent(this->body);

    return true;
}
void Raptor1::update(float dt)
{
    
}
int Raptor1::getHealthEnemy()
{
    return this->healthEnemy;
}
void Raptor1::setHealthEnemy()
{
    this->healthEnemy -= 25;
    soundexplosion = AudioEngine::play2d("sound/hit.wav");
    AudioEngine::setVolume(soundexplosion, 0.3);
    if (this->healthEnemy <= 0)
    {
        this->raptor1->removeFromParentAndCleanup(true);
        this->unschedule("RaptorShooting");
        this->soundexplosion = AudioEngine::play2d("sound/die.wav");
        AudioEngine::setVolume(soundexplosion, 0.2);

    }
}
void Raptor1::Shooting()
{
    this->soundshoot = AudioEngine::play2d("sound/laser.wav");
    AudioEngine::setVolume(soundshoot, 0.5);
    
    bullet = BulletEnemy::create();
    bullet1 = BulletEnemy::create();
    bullet2 = BulletEnemy::create();
    
    addChild(bullet);
    addChild(bullet1);
    addChild(bullet2);
    
    bullet->setPosition(Vec2((int)raptor1->getPositionX() - 15,
        (int)raptor1->getPositionY() - 10));
    bullet1->setPosition(Vec2((int)raptor1->getPositionX(),
        (int)raptor1->getPositionY() - 20));
    bullet2->setPosition(Vec2((int)raptor1->getPositionX() + 15,
        (int)raptor1->getPositionY() - 10));
    
}
void Raptor1::RaptorMove()
{
    auto moveBy = MoveBy::create(7, Vec2(0, -1000));
    this->raptor1->runAction(moveBy);

    if (this->raptor1->getPositionY() <= -20)
    {
        this->raptor1->removeFromParentAndCleanup(true);
    }
}

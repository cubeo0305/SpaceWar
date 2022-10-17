#include "Raptor2.h"
#include "AudioEngine.h"
USING_NS_CC;

Raptor2* Raptor2::createRaptor2()
{
    return Raptor2::create();
}
bool Raptor2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->maxHP = 85;
    this->healthEnemy = this->maxHP;

    this->raptor2 = Sprite::create("Viper.png");
    this->raptor2->setPosition(Vec2(random(50, 550), 850));
    this->raptor2->setScale(3);
    addChild(this->raptor2);

    this->raptor2->schedule([&](float dt)
    {
        this->Shooting();
        
        this->scheduleOnce([&](float dt)
        {
           this->Shooting();
        }, 0.5,"shot2");
        
    }, 2 , "RaptorShooting");

    this->scheduleUpdate();
    this->RaptorMove();

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->raptor2->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(32);
    this->raptor2->addComponent(this->body);

    return true;
}
void Raptor2::update(float dt)
{
    
}
int Raptor2::getHealthEnemy()
{
    return this->healthEnemy;
}
void Raptor2::setHealthEnemy()
{
    this->healthEnemy -= 25;
    
    soundexplosion = AudioEngine::play2d("sound/hit.wav");
    AudioEngine::setVolume(soundexplosion, 0.3);
    
    if (this->healthEnemy <= 0)
    {
        this->unschedule("RaptorShooting");
        this->unschedule("shot2");
        this->raptor2->removeFromParentAndCleanup(true);
        this->soundexplosion = AudioEngine::play2d("sound/die.wav");
        AudioEngine::setVolume(soundexplosion, 0.2);

    }
}
void Raptor2::Shooting()
{
    this->soundshoot = AudioEngine::play2d("sound/laser.wav");
    AudioEngine::setVolume(soundshoot, 0.5);
    
    bullet = BulletEnemy::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)raptor2->getPositionX(),
        (int)raptor2->getPositionY() - 20));
    
}
void Raptor2::RaptorMove()
{
    auto moveBy = MoveBy::create(6.5, Vec2(0, -1000));
    this->raptor2->runAction(moveBy);

    if (this->raptor2->getPositionY() <= -20)
    {
        this->raptor2->removeFromParentAndCleanup(true);
    }
}

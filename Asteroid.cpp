#include "Asteroid.h"
#include "AudioEngine.h"
USING_NS_CC;

Asteroid* Asteroid::createAsteroid()
{
    return Asteroid::create();
}
bool Asteroid::init()
{
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
    this->healthEnemy = this->maxHP;

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->asteroid->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(40);
    this->asteroid->addComponent(this->body);

    this->scheduleUpdate();

    this->AvenMove();

    return true;
}
int Asteroid::getHealthEnemy()
{
    return this->maxHP;
}
void Asteroid::setHealthEnemy()
{
    this->healthEnemy -= 25;
    sound = AudioEngine::play2d("sound/hit.wav");
    AudioEngine::setVolume(sound, 0.3);
    if (this->healthEnemy <= 0)
    {
        this->asteroid->removeFromParentAndCleanup(true);
        this->sound = AudioEngine::play2d("sound/die.wav");
        AudioEngine::setVolume(sound, 0.2);
    }
}
void Asteroid::update(float dt)
{
    
}
void Asteroid::AvenMove()
{
    auto moveBy = MoveBy::create(6, Vec2(0, -1000));
    this->asteroid->runAction(moveBy);

    if (this->asteroid->getPositionY() <= -20)
    {
        this->asteroid->removeFromParentAndCleanup(true);
    }
}

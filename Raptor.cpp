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

    //this->EnemiesMove(true);

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
    if (this->healthEnemy <= 0)
    {
        this->raptor->removeFromParentAndCleanup(true);
        this->unschedule("RaptorShooting");
    }
}
void Raptor::Shooting()
{
    bullet = BulletEnemy::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)raptor->getPositionX(),
        (int)raptor->getPositionY() - 15));
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
void Raptor::EnemiesMove(bool isStart = false)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (isStart)
    {
        this->raptor->setPosition(Vec2(visibleSize.width / 2, 900));
        auto moveDown = MoveTo::create(2, Vec2(visibleSize.width / 2, 650));
        this->raptor->runAction(Sequence::create(moveDown, CallFunc::create([&]() {
            EnemiesMove(false);
            }),nullptr));
    }
    else
    {
        int positionMax_X = visibleSize.width;
        int positionMin_X = 0;
        int positionMax_Y = visibleSize.height;
        int positionMin_Y = visibleSize.height / 2;

        int positionX = rand() % -(positionMax_X - positionMin_X + 1) + positionMin_X;
        int positionY = rand() % -(positionMax_Y - positionMin_Y + 1) + positionMin_Y;

        Vec2 position = Vec2(positionX, positionY);
        auto moveTo = MoveTo::create(2, Vec2(position));
        auto sequen = Sequence::create(moveTo, CallFunc::create([&]()
            {
                EnemiesMove(false);
            }),nullptr);
        this->raptor->runAction(sequen);
    }
}

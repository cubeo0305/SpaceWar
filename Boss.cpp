#include "Boss.h"

USING_NS_CC;

Boss* Boss::createAsteroid()
{
    return Boss::create();
}
bool Boss::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Sprite Boss
    this->boss = Sprite::create("TieF.png");
    this->boss->setPosition(Vec2(visibleSize.width/2 , 850));
    this->boss->setScale(5);
    addChild(this->boss);

    //info Boss
    this->maxHP = 1000;
    this->healthEnemy = this->maxHP;

    this->scheduleUpdate();
    this->initLis();
    this->AvenMove(true);
    this->schedule([&](float dt)
        {
            this->Shooting();
        }, 3, "BossShooting");

    return true;
}
void Boss::initLis()
{
    //PhysicsBody
    this->body = PhysicsBody::createBox(this->boss->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(50);
    this->boss->addComponent(this->body);
}
int Boss::getHealthEnemy()
{
    return this->maxHP;
}
void Boss::setHealthEnemy()
{
    this->healthEnemy -= 25;
    if (this->healthEnemy <= 0)
    {
        this->boss->removeFromParentAndCleanup(true);
        this->unschedule("BossShooting");
    }
}
void Boss::update(float dt)
{
    
}
void Boss::AvenMove(bool isStart)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (isStart)
    {
        this->boss->setPosition(Vec2(visibleSize.width / 2, 900));
        auto moveDown = MoveTo::create(2, Vec2(visibleSize.width / 2, 650));
        this->boss->runAction(Sequence::create(moveDown, CallFunc::create([&]() {
            AvenMove(false);
            }), nullptr));
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
                AvenMove(false);
            }), nullptr);
        this->boss->runAction(sequen);
    }
}
void Boss::Shooting()
{
    bullet = BulletEnemy::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)boss->getPositionX(),
        (int)boss->getPositionY() - 15));
}

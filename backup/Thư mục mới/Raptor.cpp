#include "Raptor.h"
#include "Constant.h"
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

    this->direction = Vec2(1, 1);
    this->speed = 200;

    this->raptor = Sprite::create("Viper.png");
    addChild(this->raptor);
    this->raptor->setScale(2);
    //this->raptor->setRotation(180);
    this->raptor->setPosition(Vec2(400, 400));
    this->raptor->stopAllActions();

    this->raptor->schedule([&](float dt) {
        this->Shooting();
        }, 2 , "RaptorShooting");

    this->scheduleUpdate();
    this->EnemiesMove(true);
    //info Raptor
    this->damage = 50;
    this->maxHP = 75;
    this->hp = 75;

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->raptor->getContentSize());
    this->body->setDynamic(false);
    this->raptor->addComponent(this->body);

    this->body->setContactTestBitmask(ENEMY_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(ENEMY_COLLISION_BITMASK);

    return true;
}

void Raptor::update(float dt)
{
    
}
void Raptor::Shooting()
{
    bullet = BulletEnemy::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)raptor->getPositionX(),
        (int)raptor->getPositionY() - 15));
}

void Raptor::EnemiesMove(bool isStart = false)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (isStart)
    {
        this->raptor->setPosition(Vec2(visibleSize.width / 2, 900));
        auto moveDown = MoveTo::create(1, Vec2(visibleSize.width / 2, 650));
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

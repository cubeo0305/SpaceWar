#include "Player.h"
USING_NS_CC;

Player* Player::createPlayer()
{
    return Player::create();
}

bool Player::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    this->speed = 200;
    this->direction = Vec2(1, 1);

    this->player = Sprite::create("ship1.png");
    this->player->setPosition(Vec2(300, 300));
    addChild(this->player);
    
    this->scheduleUpdate();
    this->initLis();
    this->PhysicBody();
    //this->initAnimation();

    return true;
}
//void Player::initAnimation()
//{
//    /*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/ship.plist","animation/ship.png");
//
//    this->player = Sprite::createWithSpriteFrameName("tile000.png");
//    this->player->setPosition(Vec2(300, 300));
//    this->player->setScale(3.5);
//    addChild(this->player);
//
//    
//    Animate* animate = Animate::create(Player::createAnimation("tile00", 10, 0.8f));
//    this->player->runAction(RepeatForever::create(animate));*/
//}
//Animation* Player::createAnimation(string prefixName, int pFramesOrder, float delay) 
//{
//    //Vector<SpriteFrame*> animFrames;
//    //for (int i = 0; i <= pFramesOrder; i++) {
//    //    char buffer[20] = { 0 };
//    //    sprintf(buffer, "%d.png", i);
//    //    string imgName = prefixName + buffer; // The name of image in the sprite sheet
//    //    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
//    //    animFrames.pushBack(frame);
//    //}
//    //Animation* _animation = Animation::createWithSpriteFrames(animFrames, delay);
//    //return _animation;
//}
void Player::PhysicBody()
{
    //PhysicsBody
    this->body = PhysicsBody::createBox(this->player->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(10);
    this->player->addComponent(this->body);
}
void Player::initLis()
{
    //init Mouse
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Player::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Player::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    //init keyboard
    auto lis = EventListenerKeyboard::create();
    lis->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    lis->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}
void Player::update(float dt)
{
    if (this->isKeyDown)
    {
        Vec2 curPos = this->player->getPosition();
        Vec2 newPos = curPos + (this->speed * dt * this->direction);
        this->player->setPosition(newPos);
        this->MoveCheck();
    }
}
void Player::MoveCheck()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if (this->player->getPositionX() <= 10 || this->player->getPositionX() >= visibleSize.width - 10
        || this->player->getPositionY() <= 10 || this->player->getPositionY() >= visibleSize.height - 10)
    {
        this->isKeyDown = false;
    }
    else
    {
        this->isKeyDown = true;
    }
}
void Player::onMouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

    this->setIsShooting(false);
}
void Player::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 location = e->getLocationInView();

    this->setIsShooting(true);
}
void Player::Shooting()
{
    bullet = BulletPlayer::create();
    addChild(bullet);
    bullet->setPosition(Vec2((int)player->getPositionX(),
                             (int)player->getPositionY() + 15));
}
void Player::setIsShooting(bool isShooting)
{
    if (isShooting) {
        // Shooting first bullet
        this->Shooting();

        // Schedule shooting
        this->player->schedule([&](float dt) {
            this->Shooting();
            }, 0.1, "PlayerShooting");
    }
    else {
        this->player->unschedule("PlayerShooting");
    }
}
void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        
        this->direction.y = 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        this->direction.y = -1;
        break;
    case EventKeyboard::KeyCode::KEY_A:
            this->direction.x = -1;
        break;
    case EventKeyboard::KeyCode::KEY_D:
            this->direction.x = 1;
        break;
    default:
        break;
    }

    this->isKeyDown = true;

    this->direction.normalize();
}
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
    case EventKeyboard::KeyCode::KEY_S:
        this->direction.y = 0;
        break;
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_D:
        this->direction.x = 0;
        break;
    default:
        break;
    }

    this->isKeyDown = false;

    this->direction.normalize();
}

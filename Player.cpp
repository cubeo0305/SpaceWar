#include "Player.h"
#include "Constant.h"
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

    this->player = Sprite::create("Player.png");
    this->player->setPosition(Vec2(300, 300));
    addChild(this->player);
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

    this->scheduleUpdate();

    //set Hp, damage
    this->maxHP = 100;
    this->hp = 100;
    this->damage = 35;

    //PhysicsBody
    this->body = PhysicsBody::createBox(this->player->getContentSize());
    this->body->setDynamic(false);
    this->player->addComponent(this->body);
     
    this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

    return true;
}

void Player::update(float dt)
{
    if (this->isKeyDown)
    {
        Vec2 curPos = this->player->getPosition();
        Vec2 newPos = curPos + (this->speed * dt * this->direction);
        this->player->setPosition(newPos);
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
            }, 0.3, "PlayerShooting");
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
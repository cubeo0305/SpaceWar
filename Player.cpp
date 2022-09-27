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

    this->body->setContactTestBitmask(PLAYER_CONTACT_TEST_BITMASK);
    this->body->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
    this->body->setCollisionBitmask(PLAYER_COLLISION_BITMASK);

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
void Player::Shooting() {
    // create bullet at sprite position and aim to targetPos
    auto bullet = Sprite::create("Bullet.png");
    bullet->setContentSize(Size(15, 20));
    bullet->setPosition(this->player->getPosition());
    addChild(bullet);

    auto onTop = MoveBy::create(1, Vec2(0, 700));
    auto cleanUp = CallFunc::create([=]() {
        bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onTop, cleanUp, nullptr);
    bullet->runAction(sequence);

    this->bullet->setContactTestBitmask(PLAYER_BULLET_CONTACT_TEST_BITMASK);
    this->bullet->setCategoryBitmask(PLAYER_BULLET_CATEGORY_BITMASK);
    this->bullet->setCollisionBitmask(PLAYER_BULLET_COLLISION_BITMASK);

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
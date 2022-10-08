#include "Player.h"
#include "AudioEngine.h"

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
    this->speed = 300;
    this->direction = Vec2(1, 1);
    
    this->maxHP = 100;
    hp = this->maxHP;

    /*this->player = Sprite::create("ship1.png");
    this->player->setPosition(Vec2(300, 300));
    addChild(this->player);*/
    this->scheduleUpdate();
    this->initLis();
    this->initAnimation();
    this->RunAnimation();
    this->bodys();
    return true;
}
int Player::getHealPlayer()
{
    return this->maxHP;
}
void Player::setHealPlayer()
{
    hp -= 10;
    if (hp <= 0)
    {
        this->pause();
    }
}
void Player::setHealth()
{
    hp += 50;

    if (this->hp >= 100)
    {
        hp = this->maxHP;
    }
}
void Player::initAnimation()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/ship.plist");

    this->player = Sprite::createWithSpriteFrameName("tile000.png");
    //this->player->setPosition(Vec2(300, 300));
    this->player->setScale(3.5);
    addChild(this->player);

    Animate* animate = Animate::create(Player::createAnimation("tile00", 10, 0.15));
    this->player->runAction(RepeatForever::create(animate));
}
void Player::RunAnimation()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->player->setPosition(Vec2(visibleSize.width / 2, -20));

    auto moveTo = MoveTo::create(3,Vec2(visibleSize.width/2,200));
    auto sequen = Sequence::create(moveTo,nullptr);
    this->player->runAction(sequen);
}
Animation* Player::createAnimation(string prefixName, int pFramesOrder, float delay) 
{
    Vector<SpriteFrame*> animFrames;
    for (int i = 0; i < pFramesOrder; i++) {
        char buffer[20] = { 0 };
        sprintf(buffer, "%d.png", i);
        string imgName = prefixName + buffer; // The name of image in the sprite sheet
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
        animFrames.pushBack(frame);
    }
    Animation* _animation = Animation::createWithSpriteFrames(animFrames, delay);
    return _animation;
}
void Player::bodys()
{
    //PhysicsBody
    this->body = PhysicsBody::createBox(this->player->getContentSize());
    this->body->setDynamic(false);
    this->body->setContactTestBitmask(true);
    this->body->setCollisionBitmask(1);
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
void Player::onMouseUp(Event* event) 
{
    this->setIsShooting(false);
}
void Player::onMouseDown(Event* event) 
{
    this->setIsShooting(true);
}
void Player::Shooting()
{
    

    this->soundshoot = AudioEngine::play2d("sound/laser.wav", true);

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

/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Player.h"

USING_NS_CC;

Scene* Player::createScene()
{
    return Player::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Player::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->speed = 200;
    this->direction = Vec2(1, 1);

    this->player = Sprite::create("Player.png");
    this->player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
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
    bullet->setContentSize(Size(30, 40));
    bullet->setPosition(this->player->getPosition());
    addChild(bullet);

    auto onTop = MoveBy::create(1, Vec2(0, 700));
    auto cleanUp = CallFunc::create([=]() {
        bullet->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(onTop, cleanUp, nullptr);
    bullet->runAction(sequence);

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
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->mySprite = Sprite::create("Player.png");
    addChild(this->mySprite);
    this->mySprite->setPosition(Vec2(50, 50));


    this->mySprite2 = Sprite::create("Player.png");
    addChild(this->mySprite2);
    this->mySprite2->setPosition(Vec2(300, 200));

    // Init mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


    this->initContactListener();
    this->scheduleUpdate();

    return true;
}
void HelloWorld::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

    auto moveTo = MoveTo::create(1, location);
    this->mySprite->stopAllActions();
    this->mySprite->runAction(moveTo);
}
void HelloWorld::update(float dt)
{

}
void HelloWorld::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact& contact) {
        Node* nodeA = contact.getShapeA()->getBody()->getNode();
        Node* nodeB = contact.getShapeB()->getBody()->getNode();

        if (nodeA && nodeB) {
            if (nodeA->getTag() == 10) {
                nodeB->setColor(Color3B::RED);
            }
            else if (nodeB->getTag() == 10) {
                nodeA->setColor(Color3B::RED);
            }
        }
        return true;
    };
    contactListener->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // init physic body
    auto physicsBody = PhysicsBody::createCircle(this->mySprite->getContentSize().width / 2);
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0x01); //0001
    physicsBody->setCategoryBitmask(0x01); // 0001
    physicsBody->setCollisionBitmask(0x01); // 0001
    this->mySprite->addComponent(physicsBody);
    this->mySprite->setTag(10); // identity for mySprite

    auto physicsBody2 = PhysicsBody::createCircle(this->mySprite2->getContentSize().width / 2);
    physicsBody2->setDynamic(false);
    physicsBody2->setContactTestBitmask(0x01); // 0010 
    physicsBody2->setCategoryBitmask(0x03); // 0011
    physicsBody2->setCollisionBitmask(0x01); // 0001
    this->mySprite2->addComponent(physicsBody2);
    this->mySprite2->setTag(1); //identity for mySprite2
}
void HelloWorld::onContactSeparate(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {
        nodeA->setColor(Color3B::WHITE);
        nodeB->setColor(Color3B(255, 255, 255));
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

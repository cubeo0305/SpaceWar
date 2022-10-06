#include "GameScene.h"
#include "Enemy.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool GameScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->Wave = 0;

    //backgournd
    auto bg = Sprite::create("space.png");
    bg->setContentSize(Size(visibleSize.width, visibleSize.height));
    bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

    this->planet = Sprite::create("ring.png");
    this->planet->setRotation(90);
    this->planet->setAnchorPoint(Vec2(0, 0));
    this->planet->setPosition(Vec2(0,770));
    this->planet->setScale(5);
    addChild(this->planet);

    this->schedule([&](float dt)
        {
            this->ActionPlane();

        }, 2, "ActionPlane");

    player = Player::create();
    addChild(player);

    this->schedule([&](float dt)
        {
            this->SpawnEnemies();
        }, 6.5, "SpawnEnemies");

    this->WaveEnemies();
    this->initContactListener();

    return true;
}
void GameScene::ActionPlane()
{
    auto moveTo = MoveTo::create(1,Vec2(0,770));
    auto point1 = MoveTo::create(1, Vec2(1,771));
    auto sequen = Sequence::create(moveTo, point1, moveTo, nullptr);
    this->planet->runAction(sequen);
}
void GameScene::SpawnEnemies()
{
    asteroid = Asteroid::create();
    addChild(asteroid);

    raptor = Raptor::create();
    addChild(raptor);

    savenger = Savenger::create();
    addChild(savenger);

    this->WaveEnemies();

    CCLOG("1");
}
void GameScene::WaveEnemies()
{   
    this->Wave -= 1;
    if (this->Wave <= 0)
    {
        this->unschedule("SpawnEnemies");
        boss = Boss::create();
        addChild(boss);
    }
}
void GameScene::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
bool GameScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody();
    auto nodeB = contact.getShapeB()->getBody();

    //Savenger 
    if (nodeA->getCollisionBitmask() == 15 && nodeB->getCollisionBitmask() == 20 ||
        nodeB->getCollisionBitmask() == 20 && nodeA->getCollisionBitmask() == 15)
    {
        if (nodeA->getCollisionBitmask() == 15)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                nodeA->getNode()->removeFromParentAndCleanup(true);

                auto savengerBody = dynamic_cast<Savenger*>(nodeB->getNode());
                this->savenger->setHealthEnemy();
            }
        }
        if (nodeB->getCollisionBitmask() == 15)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                nodeB->getNode()->removeFromParentAndCleanup(true);

                auto savengerBody = dynamic_cast<Savenger*>(nodeA->getNode());
                this->savenger->setHealthEnemy();
            }
        }
    }
    //Raptor
    if (nodeA->getCollisionBitmask() == 15 && nodeB->getCollisionBitmask() == 30 ||
        nodeB->getCollisionBitmask() == 30 && nodeA->getCollisionBitmask() == 15)
    {
        if (nodeA->getCollisionBitmask() == 15)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                nodeA->getNode()->removeFromParentAndCleanup(true);

                auto raptorBody = dynamic_cast<Raptor*>(nodeB->getNode());
                this->raptor->setHealthEnemy();
            }
        }
        if (nodeB->getCollisionBitmask() == 15)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                nodeB->getNode()->removeFromParentAndCleanup(true);

                auto raptorBody = dynamic_cast<Raptor*>(nodeA->getNode());
                this->raptor->setHealthEnemy();
            }
        }
    }
    //Asteroid
    if (nodeA->getCollisionBitmask() == 15 && nodeB->getCollisionBitmask() == 40 ||
        nodeB->getCollisionBitmask() == 40 && nodeA->getCollisionBitmask() == 15)
    {
        if (nodeA->getCollisionBitmask() == 15)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                nodeA->getNode()->removeFromParentAndCleanup(true);

                auto AsteroidBody = dynamic_cast<Asteroid*>(nodeB->getNode());
                this->asteroid->setHealthEnemy();
            }
        }
        if (nodeB->getCollisionBitmask() == 15)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                nodeB->getNode()->removeFromParentAndCleanup(true);

                auto AsteroidBody = dynamic_cast<Asteroid*>(nodeB->getNode());
                this->asteroid->setHealthEnemy();
            }
        }
    }
    //Boss
    if (nodeA->getCollisionBitmask() == 15 && nodeB->getCollisionBitmask() == 50 ||
        nodeB->getCollisionBitmask() == 50 && nodeA->getCollisionBitmask() == 15)
    {
        if (nodeA->getCollisionBitmask() == 15)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                nodeA->getNode()->removeFromParentAndCleanup(true);

                auto BossBody = dynamic_cast<Boss*>(nodeB->getNode());
                this->boss->setHealthEnemy();
            }
        }
        if (nodeB->getCollisionBitmask() == 15)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                nodeB->getNode()->removeFromParentAndCleanup(true);

                auto BossBody = dynamic_cast<Boss*>(nodeB->getNode());
                this->boss->setHealthEnemy();
            }
        }
    }

    return true;
}
void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

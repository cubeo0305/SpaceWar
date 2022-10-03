#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    player = Player::create();
    addChild(player);

    this->schedule([&](float dt)
    {
        this->SpawnEnemies();
            
    }, 3, "SpawnEnemies");

    savenger = Savenger::create();
    addChild(savenger);

    /*raptor = Raptor::create();
    addChild(raptor);*/

    //this->SpawnEnemies();

    /*for (int i = 0; i < 4 + random(0, 1); i++)
    {
        this->SpawnEnemies();
    }*/

    this->initContactListener();

    return true;
}
void GameScene::SpawnEnemies()
{
    /*auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int posiXmax = visibleSize.width;
    int PosiXmin = 0;
    int posiX = rand() % (posiXmax - PosiXmin + 1) + PosiXmin;

    Vec2 position = Vec2(posiX, 650);

    //random Enemies
    int intMaxEnemies = 1;
    int intMinEnemies = 0;
    int enemyType = rand() % (intMaxEnemies - intMinEnemies + 1) + intMinEnemies;

    switch (enemyType)
    {
    case Enemy::Raptor:
        raptor = Raptor::create();
        addChild(raptor);
        break;
    case Enemy::Savenger:
        savenger = Savenger::create();
        addChild(savenger);
        break;
    default:
        savenger = Savenger::create();
        addChild(savenger);
        break;
    }
    savenger->setPosition(Vec2(position));*/

    savenger = Savenger::create();
    addChild(savenger);

    /*raptor = Raptor::create();
    addChild(raptor);*/
    
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
    return true;
}
void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

#include "GameScene.h"
#include "GameManager.h"
#include "Constant.h"
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
    
    //background
    auto background = Sprite::create("space.png");
    background->setPosition(Vec2(0,0));
    background->setAnchorPoint(Vec2(0,0));
    background->setContentSize(Size(visibleSize.width,visibleSize.height));
    addChild(background);

    auto Ring = Sprite::create("ring.png");
    Ring->setAnchorPoint(Vec2(0, 0));
    Ring->setPosition(Vec2(0,770));
    Ring->setRotation(90);
    Ring->setScale(5);
    addChild(Ring);

    //player add
    player = Player::create();
    addChild(player);

    this->schedule([&](float dt)
        {
            this->SpawnEnemies();
        }, 2, "SpawnEnemies");

    savenger = Savenger::create();
    addChild(savenger);

    raptor = Raptor::create();
    addChild(raptor);

    this->initContactListener();

    return true;
}
void GameScene::SpawnEnemies()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
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
    /*case Entity::Raptor:
        raptor = Raptor::create();
        addChild(raptor);
        break;
    case Entity::Savenger:
        savenger = Savenger::create();
        addChild(savenger);
        break;*/
    /*case Entity::Asteroid:
        asteroid = Asteroid::create();
        addChild(asteroid);
        break;*/
    default:
        asteroid = Asteroid::create();
        addChild(asteroid);
        break;
    }
    //asteroid->setPosition(Vec2(position));
}
void GameScene::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        Entity* entityA = GameManager::findEntity((Sprite*)nodeA);
        Entity* entityB = GameManager::findEntity((Sprite*)nodeB);
        float damageA = entityA->getDamage();
        float damageB = entityB->getDamage();
        entityA->TakeDamage(damageB);
        entityB->TakeDamage(damageA);
    }

    return true;
}

void GameScene::onContactSeparate(PhysicsContact& contact) {
    Node* nodeA = contact.getShapeA()->getBody()->getNode();
    Node* nodeB = contact.getShapeB()->getBody()->getNode();
}
void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

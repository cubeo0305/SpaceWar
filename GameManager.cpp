#include "GameManager.h"

USING_NS_CC;

Scene* GameManager::createScene()
{
    return GameManager::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameManager::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}

void GameManager::Start()
{
    
    
}

void GameManager::SpawnEnemies()
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
    case Entity::Raptor:
        raptor = Raptor::create();
        addChild(raptor);
        break;
    case Entity::Savenger:
        savenger = Savenger::create();
        addChild(savenger);
        break;
    default:
        savenger = Savenger::create();
        addChild(savenger);
        break;
    }
    savenger->setPosition(Vec2(position));
}

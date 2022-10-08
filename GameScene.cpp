#include "GameScene.h"
#include "Enemy.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
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
    
    this->Wave = 4; 
    this->damage = 0;

    this->schedule([&](float dt)
        {
            this->ActionPlane();

        }, 2, "ActionPlane");
    this->schedule([&](float dt)
        {
            this->cloud();
        }, 3, "cloud");
    this->BackGround();
    player = Player::create();
    addChild(player);

    this->scheduleUpdate();
    this->InitGame();

    return true;
}
void GameScene::InitGame()
{
    this->WaveEnemies();
    this->initContactListener();
    this->initPlayerUI();

    this->schedule([&](float dt)
        {
            this->SpawnEnemies();
        }, 6.5, "SpawnEnemies");
    this->schedule([&](float dt)
        {
            this->PlayerDie();
        }, 0.01, "test");
    this->schedule([&](float dt)
        {
            this->HealthPlayer();
        }, 13, "Healing");
}
void GameScene::update(float dt)
{
    this->updatePlayerUI();
}
void GameScene::cloud()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->clouds = Sprite::create("stars.png");
    this->clouds->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->clouds->setPosition(Vec2(visibleSize.width/2, 850));
    this->clouds->setRotation(180/2);
    addChild(this->clouds);

    auto moveby = MoveBy::create(5,Vec2(0,-1000));
    auto cleanUp = CallFunc::create([=]() {
        if (this->clouds->getPositionY() <= 0)
        {
            this->clouds->removeFromParentAndCleanup(true);
        }
        });
    auto sequenc = Sequence::create(moveby,cleanUp, nullptr);
    this->clouds->runAction(sequenc);
}
void GameScene::initPlayerUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->playerInfo = Node::create();
    playerInfo->setAnchorPoint(Vec2(0, 0));
    playerInfo->setPosition(Vec2(0, 10));
    
    //damage
    this->damgeNode = Node::create();
    Sprite* damage = Sprite::create("damage.png");
    damage->setPosition(Vec2(visibleSize.width - 65, visibleSize.height - 20));
    damage->setContentSize(Size(20, 20));
    
    Label* damageLabel = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 20);
    damageLabel->setName("damageLabel");
    damageLabel->setAnchorPoint(Vec2(0, 0.5));
    damageLabel->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 23));
    addChild(this->damgeNode);
    this->damgeNode->addChild(damage);
    this->damgeNode->addChild(damageLabel);

    // HP
    Sprite* hpBarBG = Sprite::create("hpBarBG.png");
    hpBarBG->setName("hpBarBG");
    hpBarBG->setContentSize(Size(200, 20));
    hpBarBG->setAnchorPoint(Vec2(0, 0.5));

    Sprite* hpBar = Sprite::create("hpBar.png");
    hpBar->setName("hpBar");
    hpBar->setContentSize(Size(200, 20));
    hpBar->setAnchorPoint(Vec2(0, 0.5));

    // Heart: Heart Count & Heart Icon
    Node* heart = Node::create();
    heart->setName("heart");
    heart->setAnchorPoint(Vec2(0, 0.5));

    Label* heartLabel = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 20);
    heartLabel->setName("heartLabel");
    heartLabel->setAnchorPoint(Vec2(0, 0.5));

    Sprite* heartIcon = Sprite::create("heart1.png");
    heartIcon->setContentSize(Size(20, 20));
    heartIcon->setAnchorPoint(Vec2(0, 0.5));
    const float padding = 8;

    heartIcon->setPosition(Vec2(0,0));
    heart->setPosition(Vec2(0,hpBarBG->getContentSize().height));
    heart->addChild(heartLabel);
    
    playerInfo->addChild(hpBarBG);
    playerInfo->addChild(hpBar);
    playerInfo->addChild(heart);
    playerInfo->addChild(heartIcon);
    addChild(playerInfo);
}
void GameScene::updatePlayerUI()
{
    auto hpBarBG = this->playerInfo->getChildByName("hpBarBG");
    auto hpBar = this->playerInfo->getChildByName("hpBar");
    auto heartLabel = this->playerInfo->getChildByName("heart")->getChildByName("heartLabel");
    auto damageLabel = this->damgeNode->getChildByName("damageLabel");

    const Size hpBarMaxSize = hpBarBG->getContentSize();
    Size hpBarSize = hpBarMaxSize;

    hpBarSize.width = this->player->hp / this->player->maxHP * hpBarMaxSize.width;
    hpBar->setContentSize(hpBarSize);

    ((Label*)heartLabel)->setString(std::to_string(this->player->hp));

    ((Label*)damageLabel)->setString(std::to_string(this->damage));
}
void GameScene::ActionPlane()
{
    auto moveTo = MoveTo::create(1,Vec2(0,770));
    auto point1 = MoveTo::create(1, Vec2(1,771));
    auto sequen = Sequence::create(moveTo, point1, moveTo, nullptr);
    this->planet->runAction(sequen);
}
void GameScene::BackGround()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //backgournd
    auto bg = Sprite::create("bg_01.png");
    bg->setContentSize(Size(visibleSize.width, visibleSize.height));
    bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

    this->planet = Sprite::create("ring.png");
    this->planet->setRotation(90);
    this->planet->setAnchorPoint(Vec2(0, 0));
    this->planet->setPosition(Vec2(0, 770));
    this->planet->setScale(5);
    addChild(this->planet);
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
}
void GameScene::WaveEnemies()
{   
    this->Wave -= 1;
    if (this->Wave <= 0)
    {
        this->unschedule("SpawnEnemies");
        boss = Boss::create();
        addChild(boss);

        boss->player = this->player;
    }
}
void GameScene::initContactListener() {
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void GameScene::PlayerDie()
{
    if (this->player->hp <= 0)
    {
        auto hello = HelloWorld::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, hello));
    }
}
void GameScene::HealthPlayer()
{
    healing = Health::create();
    addChild(healing);
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
                this->damage += 25;
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
                this->damage += 25;
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
                this->damage += 1;
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
                this->damage += random(17,25);
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
    //BossGun vs Player
    if (nodeA->getCollisionBitmask() == 25 && nodeB->getCollisionBitmask() == 1 ||
        nodeB->getCollisionBitmask() == 1 && nodeA->getCollisionBitmask() == 25)
    {
        if (nodeA->getCollisionBitmask() == 25)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                nodeA->getNode()->removeFromParentAndCleanup(true);

                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();
            }
        }
        if (nodeB->getCollisionBitmask() == 25)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                nodeB->getNode()->removeFromParentAndCleanup(true);

                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();
            }
        }
    }
    //Asteroid vs Player
    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 40 ||
        nodeB->getCollisionBitmask() == 40 && nodeA->getCollisionBitmask() == 1)
    {
        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeB->getNode()->removeFromParentAndCleanup(true);
            }
        }
        if (nodeB->getCollisionBitmask() == 1)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeA->getNode()->removeFromParentAndCleanup(true);
            }
        }
    }
    //Savenger vs Player
    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 20 ||
        nodeB->getCollisionBitmask() == 20 && nodeA->getCollisionBitmask() == 1)
    {
        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeB->getNode()->removeFromParentAndCleanup(true);
            }
        }
        if (nodeB->getCollisionBitmask() == 1)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeA->getNode()->removeFromParentAndCleanup(true);
            }
        }
        return true;
    }
    //Raptor vs Player
    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 30 ||
        nodeB->getCollisionBitmask() == 30 && nodeA->getCollisionBitmask() == 1)
    {
        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeB->getNode()->removeFromParentAndCleanup(true);
            }
        }
        if (nodeB->getCollisionBitmask() == 1)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();

                nodeA->getNode()->removeFromParentAndCleanup(true);
            }
        }
    }
    //Boss vs Player
    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 50 ||
        nodeB->getCollisionBitmask() == 50 && nodeA->getCollisionBitmask() == 1)
    {
        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                //nodeA->getNode()->removeFromParentAndCleanup(true);
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();
            }
        }
        if (nodeB->getCollisionBitmask() == 1)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                //nodeB->getNode()->removeFromParentAndCleanup(true);
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealPlayer();
            }
        }
    }
    //Healing
    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 2 ||
        nodeB->getCollisionBitmask() == 2 && nodeA->getCollisionBitmask() == 1)
    {
        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealth();
                nodeB->getNode()->removeFromParentAndCleanup(true);
            }
        }
        if (nodeB->getCollisionBitmask() == 1)
        {
            if (nodeB->getNode() != nullptr && nodeA->getNode())
            {
                auto Body = dynamic_cast<Player*>(nodeB->getNode());
                this->player->setHealth();
                nodeA->getNode()->removeFromParentAndCleanup(true);
            }
        }
    }
}
void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

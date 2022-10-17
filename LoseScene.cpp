#include "LoseScene.h"
#include "GameScene.h"
#include "AudioEngine.h"
#include "MainMenuGame.h"
USING_NS_CC;

int dmg = 0;

Scene* LoseScene::createScene(int _dmg)
{
    dmg = _dmg;
    return LoseScene::create();
}
bool LoseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("bg_01.png");
    bg->setAnchorPoint(Vec2(0,0));
    bg->setContentSize(Size(visibleSize));
    addChild(bg);
    
    auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(LoseScene::onMouseDown, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    auto myLabel = Label::createWithTTF("Mission Failed", "fonts/Marker Felt.ttf", 50);
        myLabel->setTextColor(Color4B(255, 255, 255, 100));
        myLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
        myLabel->enableShadow(Color4B::YELLOW);
        myLabel->enableOutline(Color4B(255, 0, 0, 255), 1);
        myLabel->enableGlow(Color4B(200, 20, 0, 255));
        addChild(myLabel);
    
    std::string str = "Score: " +  std::to_string(dmg);
    
    auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 35);
    addChild(label);
    label->setPosition(visibleSize.width/2,550);
    
    Vector<MenuItem*> menuItems = {
        MenuItemImage::create("backgrounds/back.png","backgrounds/back.png"  , [&](Ref* sender) {
               this->sound = AudioEngine::play2d("sound/select.wav");
               auto as = MainMenuGame::createScene();
               Director::getInstance()->replaceScene(TransitionFade::create(0.5, as));
           }),
        MenuItemImage::create("backgrounds/re.png","backgrounds/re.png"  , [&](Ref* sender) {
               this->sound = AudioEngine::play2d("sound/select.wav");
               auto hello = GameScene::createScene();
               Director::getInstance()->replaceScene(TransitionFade::create(0.5, hello));
           }),
       };

        auto menu = Menu::createWithArray(menuItems);
        addChild(menu);
        menu->setScale(0.5);
        menu->setAnchorPoint(Vec2(0,0));
        menu->alignItemsHorizontallyWithPadding(10);
        menu->setPosition(visibleSize/2);
    
    AudioEngine::preload("sound/lose.wav");
    scheduleOnce([&](float dt)
    {
        soundLose = AudioEngine::play2d("sound/lose.wav");
    }, 0.5,"deplay");
    
    this->scheduleUpdate();
    
    return true;
}
void LoseScene::update(float dt)
{
    
}
void LoseScene::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();
}

void LoseScene::menuCloseCallback(Ref* pSender)
{
    
    Director::getInstance()->end();
}

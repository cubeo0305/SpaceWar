#include "MainMenuGame.h"
#include "GameScene.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* MainMenuGame::createScene()
{
    return MainMenuGame::create();
}
bool MainMenuGame::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    AudioEngine::preload("menu.wav");
    soundmenu = AudioEngine::play2d("menu.wav");
    
    
    this->initGame();
    this->scheduleUpdate();
    
    return true;
}
void MainMenuGame::initGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("bg_01.png");
    bg->setAnchorPoint(Vec2(0,0));
    bg->setContentSize(Size(visibleSize));
    addChild(bg);
    
    auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(MainMenuGame::onMouseDown, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    auto myLabel = Label::createWithTTF("Space Wars", "fonts/Marker Felt.ttf", 50);
        myLabel->setTextColor(Color4B(255, 255, 255, 100));
        myLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
        myLabel->enableShadow(Color4B::YELLOW);
        myLabel->enableOutline(Color4B(255, 0, 0, 255), 1);
        myLabel->enableGlow(Color4B(200, 20, 0, 255));
    addChild(myLabel);
    
    //menu
    
    Vector<MenuItem*> menuItems = {
            MenuItemImage::create("backgrounds/Start_BTN.png","backgrounds/Start_BTN.png", [&](Ref* sender) {
                this->sound = AudioEngine::play2d("sound/select.wav");
                AudioEngine::pause(this->soundmenu);
                auto play = GameScene::create();
                Director::getInstance()->replaceScene(TransitionFade::create(1,play));
            }),
            MenuItemImage::create("backgrounds/Exit.png","backgrounds/Exit.png", [&](Ref* sender) {
                this->sound = AudioEngine::play2d("sound/select.wav");
                Director::getInstance()->end();
            }),
        };

        auto menu = Menu::createWithArray(menuItems);
        addChild(menu);
        //menu->alignItemsVertically();
        menu->alignItemsVerticallyWithPadding(10);
        //menu->alignItemsHorizontallyWithPadding(3);
        menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}
void MainMenuGame::update(float dt)
{
    
}
void MainMenuGame::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

}
void MainMenuGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

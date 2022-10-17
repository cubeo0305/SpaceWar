#include "HelloWorldScene.h"
#include "GameScene.h"
#include "AudioEngine.h"
#include "MainMenuGame.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
int score = 0;

Scene* HelloWorld::createScene(int _score)
{
    score = _score;
    return HelloWorld::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool HelloWorld::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    auto bg = Sprite::create("bg_01.png");
    bg->setAnchorPoint(Vec2(0,0));
    bg->setContentSize(Size(visibleSize));
    addChild(bg);
    //output dmg
    auto myLabel = Label::createWithTTF("Victory", "fonts/Marker Felt.ttf", 50);
        myLabel->setTextColor(Color4B(255, 255, 255, 100));
        myLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
        myLabel->enableShadow(Color4B::YELLOW);
        myLabel->enableOutline(Color4B(255, 0, 0, 255), 1);
        myLabel->enableGlow(Color4B(200, 20, 0, 255));
        addChild(myLabel);
    
    std::string str = "Score: " +  std::to_string(score);
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
    
    AudioEngine::preload("sound/win.wav");
    scheduleOnce([&](float dt)
    {
        soundWin = AudioEngine::play2d("sound/win.wav");
    }, 0.7,"deplay");
    
    this->scheduleUpdate();

    return true;
}
void HelloWorld::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;

    Vec2 location = e->getLocationInView();

    

}
void HelloWorld::update(float dt)
{

}
void HelloWorld::initContactListener() {
   
}
void HelloWorld::onContactSeparate(PhysicsContact& contact) {
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

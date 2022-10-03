#include "GameManager.h"
#include "Entity.h"
#include "Player.h"
#include "Raptor.h"
#include "Savenger.h"

USING_NS_CC;

Scene* GameManager::world = NULL;
std::vector<Entity*> GameManager::enemies;
std::vector<Entity*> GameManager::entities;

GameManager::GameManager() {
}

GameManager::~GameManager() {

}
void GameManager::setWorld(Scene* world) {
	GameManager::world = world;
}

Scene* GameManager::getWorld() {
	return GameManager::world;
}

bool GameManager::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}
Entity* GameManager::findEntity(Sprite* sprite) {
	for (Entity* entity : entities) {
		if (entity != NULL) {
			if (entity->getSprite() == sprite) return entity;
		}
	}

	return NULL;
}
void GameManager::destroyEntity(Entity* entity) {
	auto _entity = std::find(entities.begin(), entities.end(), entity);
	auto _enemy = std::find(enemies.begin(), enemies.end(), entity);

	/*std::remove(entities.begin(), entities.end(), entity);
	std::remove(enemies.begin(), enemies.end(), entity);*/
	entity->destroy();
	delete entity;

	if (_entity != entities.end()) (*_entity) = NULL;
	if (_enemy != enemies.end()) (*_enemy) = NULL;
}
void GameManager::addEntity(Entity* entity) {
	auto foundEntity = std::find(entities.begin(), entities.end(), entity);
	if (foundEntity == entities.end()) {
		world->addChild(entity->getSprite());
		entities.push_back(entity);
	}
}

void GameManager::Start()
{
    
    
}

void GameManager::SpawnEnemies()
{

}

#include "Entity.h"
#include "GameManager.h"
USING_NS_CC;

Entity::Entity()
{

}

Entity::Entity(const string& file)
{
	this->sprite = Sprite::create(file);
}

Entity::~Entity()
{

}
void Entity::init()
{
	this->maxHP = 0;
	this->hp = 0;
	this->damage = 0;
}

float Entity::getHP() {
	return this->hp;
}

void Entity::setHP(float hp) {
	this->hp = hp;
}
float Entity::getMaxHP()
{
	return this->maxHP;
}
void Entity::setMaxHP(float maxHP)
{
	this->maxHP = maxHP;
}
float Entity::getDamage() {
	return this->damage;
}

void Entity::setDamage(float damage) {
	this->damage = damage;
}

void Entity::TakeDamage(float damage) {
	this->hp -= damage;

	if (this->hp <= 0) {
		this->hp = 0;
		
		GameManager::destroyEntity(this);
	}
}
Sprite* Entity::getSprite() {
	return this->sprite;
}
void Entity::destroy() {
	this->sprite->removeFromParentAndCleanup(true);
	/*this->sprite->setPosition(Vec2(-100, -100));
	this->sprite->stopAllActions();*/
}
#include "Entity.h"

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
int Entity::getHealthEnemy()
{
	return this->healthEnemy;
}

void Entity::setHealthEnemy(float hp)
{
	this->healthEnemy = hp;
}
float Entity::getMaxHP()
{
	return this->maxHP;
}
void Entity::setMaxHP(float maxHP)
{
	this->maxHP = maxHP;
}
float Entity::getDamage()
{
	return this->damage;
}
void Entity::setDamage(float damage)
{
	this->damage = damage;
}
void Entity::TakeDamage(float damage)
{
	this->hp -= damage;
}
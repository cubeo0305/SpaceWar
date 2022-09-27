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
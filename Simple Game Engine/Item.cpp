#include "Item.h"

#include "Assets.h"

const Item Item::None = Item{ "Null","Iron" };
const Item Item::Iron = Item{ "Iron","Iron" };
const Item Item::Silver = Item{ "S","Silver" };

Item::Item(std::string iName, std::string tex):
	itemName(iName),
	tName(tex),
	texture(Assets::getTexture(tex))
{
	this->loadTexture();
}


Item::Item(const Item& other):
	itemName(other.itemName),
	tName(other.tName),
	texture(Assets::getTexture(tName))
{
}

Item& Item::operator=(const Item& it)
{
	this->itemName = it.itemName;
	this->tName = it.tName;
	this->texture = it.texture;
	return *this;
}

void Item::loadTexture()
{
	texture = Assets::getTexture(tName);
}

bool Item::isNull()
{
	return itemName.compare(Item::None.itemName)==0;
}

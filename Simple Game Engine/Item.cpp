#include "Item.h"

#include "Assets.h"

const Item Item::None = Item{ "Null","Iron" };
const Item Item::Iron = Item{ "Iron","Iron" };
const Item Item::Silver = Item{ "Silver","Silver" };

Item::Item(std::string iName, std::string tex):
	itemName(iName),
	tName(tex),
	texture(Assets::getTexture(tex))
{
}


Item& Item::operator=(const Item& it)
{
	this->itemName = it.itemName;
	this->tName = it.tName;
	this->loadTexture();
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

#include "Item.h"

#include "Assets.h"

const Item Item::None= Item{ "Null",Assets::getTexture("TestItem") };
const Item Item::Test = Item{ "Test",Assets::getTexture("TestItem") };

bool Item::isNull()
{
	return itemName.compare(Item::None.itemName)==0;
}

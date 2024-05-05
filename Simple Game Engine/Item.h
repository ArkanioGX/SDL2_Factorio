#pragma once
#include <string>
#include "Texture.h"

//TODO : Item placeholder

struct Item
{
public:
	std::string itemName;
	Texture& texture;

	const static Item None;
	const static Item Test;

	Item(std::string iName, Texture& tex ) :
		itemName(iName),
		texture(tex)
	{}

	Item(const Item& other) :
		itemName(other.itemName),
		texture(other.texture) 
	{}

	bool isNull();

	Item operator=(const Item other)
	{
		return other;
	}
};

inline bool operator==(const Item& r, const Item& l) {
	return r.itemName.compare(l.itemName) == 0;
}




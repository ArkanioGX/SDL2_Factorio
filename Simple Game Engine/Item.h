#pragma once
#include <string>
#include "Texture.h"

//TODO : Item placeholder

struct Item
{
public:
	std::string itemName;
	Texture& texture;

	Item(std::string iName, Texture& tex ) :
		itemName(iName),
		texture(tex)
	{}

	
	Item(const Item& other) :
		itemName(other.itemName),
		texture(other.texture) 
	{}

	Item& operator=(const Item& it) {
		this->itemName = it.itemName;
		this->texture = it.texture;
		return *this;
	}

	bool isNull();

	static const Item None;
	static const Item Test;
};

inline bool operator==(const Item& r, const Item& l) {
	return r.itemName.compare(l.itemName) == 0;
}




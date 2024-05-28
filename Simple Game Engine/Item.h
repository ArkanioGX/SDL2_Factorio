#pragma once
#include <string>
#include "Texture.h"
#include "Assets.h"

//TODO : Item placeholder

struct Item
{
public:
	std::string itemName;
	std::string tName;
	Texture& texture;

	Item(std::string iName, std::string tex);
		

	
	Item(const Item& other) :
		itemName(other.itemName),
		texture(other.texture) 
	{}

	Item& operator=(const Item& it);

	void loadTexture();

	bool isNull();

	static const Item None;
	static const Item Iron;
	static const Item Silver;
};

inline bool operator==(const Item& r, const Item& l) {
	return r.itemName.compare(l.itemName) == 0;
}




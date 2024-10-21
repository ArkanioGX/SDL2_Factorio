#pragma once
#include "Tile.h"
#include <vector>
#include "Item.h"

struct ItemContainer {
	Item item;
	float baseT = 0;
	float t = 0;
	int iSize = 1;
	bool hasItem() {
		return !item.isNull();
	}
	bool isBlocked = false;
	int inSide = 0;

};



enum IOType {
	Output,
	Input
}
;

struct ItemRenderContainer {
public:
	Vector2 pos;
	Texture tex;
};

class MachineTile : public Tile
{
public:

	MachineTile(): Tile(),inputTile({}), outputTile({}) {
		connectToNearby();
	};

	MachineTile(std::string tname, int tID, float rot, bool cRot) : Tile(tname,tID, rot, cRot, false, Type::Machine, PlaceableOn::Everything) {
		connectToNearby();
	};

	MachineTile(const MachineTile& other) :
		Tile(other.tileName,other.tileID,other.rotation,other.canRotate,false, Type::Machine, PlaceableOn::Everything),
		inputTile(other.inputTile),
		outputTile(other.outputTile)
	{
		connectToNearby();
	}

	~MachineTile();

	Tile* copy() override;

	Vector2 currentPos = Vector2::zero;

	class MachineTileComponent* ownerComponent;

	std::vector<MachineTile*> inputTile, outputTile;
	virtual void update(float dt);
	virtual std::vector<ItemRenderContainer> additiveDraw();

	/// <summary>
	/// Gives the item to the tile and send a bool to confirm if the item is passed well
	/// </summary>
	/// <param name="it"> The current Item Container which the item we want to pass is in </param>
	/// <param name="side"> </param>
	/// <returns></returns>
	virtual bool giveItem(ItemContainer* it, int side);

	virtual void connectToNearby();
	virtual bool canConnect(int side, IOType io, MachineTile* mt);

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);

	void ClearAllIO();

	Vector2 getPosFromSide(int s) {
		switch (s) {
		case 0:
			return Vector2(-1, 0);
		case 1:
			return Vector2(0, 1);
		case 2:
			return Vector2(1, 0);
		case 3:
			return Vector2(0, -1);
		}
		return Vector2(0, 0);
	}

	int getSideFromPos(Vector2 p) {
		
		if (p.x == 0) {
			if (p.y == 1) {
				return 1;
			}
			else {
				return 3;
			}
		}
		else {
			if (p.x == 1) {
				return 2;
			}
			else {
				return 0;
			}
		}
		return 4;
	}

	Vector2 getDiffPos(MachineTile* mt) {
		return this->currentPos - mt->currentPos;
	}
};

struct IOTile {
	MachineTile* mTile = nullptr;
	int side = 0;
};




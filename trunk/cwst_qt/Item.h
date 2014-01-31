#include <windows.h>
#include "BinaryReader.h"

#pragma once

class ItemUpgrade
{
public:
	ItemUpgrade(void);
	~ItemUpgrade(void);
	void Read(BinaryReader * reader);

	byte X, Y, Z, Material;
	unsigned int Level;
};

class Item
{
public:
	Item(void);
	~Item(void);
	void Read(BinaryReader * reader);

	byte Type, SubType;
	short Modifier;
	short MinusModifier;
	byte Rarity, Material, Flags;
	short Level;
	ItemUpgrade Upgrades[32];
	unsigned int UpgradeCount;
};


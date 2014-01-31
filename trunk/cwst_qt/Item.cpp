#include "Item.h"

void ItemUpgrade::Read(BinaryReader * reader)
{
	X = reader->ReadByte();
	Y = reader->ReadByte();
	Z = reader->ReadByte();
	Material = reader->ReadByte();
	Level = reader->ReadUInt();
}

ItemUpgrade::ItemUpgrade(void)
{
}


ItemUpgrade::~ItemUpgrade(void)
{
}

void Item::Read(BinaryReader * reader)
{
	Type = reader->ReadByte();
	SubType = reader->ReadByte();
	reader->ReadUInt16(); // skip 2
	Modifier = reader->ReadUInt();
	MinusModifier = reader->ReadUInt();
	Rarity = reader->ReadByte();
	Material = reader->ReadByte();
	Flags = reader->ReadByte();
	reader->ReadByte(); // skip 1
	Level = reader->ReadInt16();
	reader->ReadInt16(); // skip 2
	for (int i = 0; i < 32; ++i)
	{
		Upgrades[i] = *new ItemUpgrade();
		Upgrades[i].Read(reader);
	}
	UpgradeCount = reader->ReadUInt();
}


Item::Item(void)
{
}


Item::~Item(void)
{
	//delete[] Upgrades;
}

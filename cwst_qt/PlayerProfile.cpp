#include "PlayerProfile.h"


PlayerProfile::PlayerProfile(void)
{
	appearance = *new Appearance();
}

void PlayerProfile::Read(BinaryReader reader)
{
	/*
	br.MoveTo(388);
	Level = br.ReadDword();
	br.MoveTo(4386);
	Name = br.ReadString();
	*/
	reader.ReadUInt64();
	LastBitmask = reader.ReadBytes(8);
	//BitArray bitArray = new BitArray(LastBitmask);
	std::bitset<8 * CHAR_BIT> bitArray;

	for(int i = 0; i < 8; ++i)
	{
		byte cur = LastBitmask[i];
		int offset = i * CHAR_BIT;

		for(int bit = 0; bit < CHAR_BIT; ++bit)
		{
			bitArray[offset] = cur & 1;
			++offset;   // Move to next bit in b
			cur >>= 1;  // Move to next bit in array
		}
	}

	if (bitArray[0])
	{
		Position = new QVector3(reader.ReadInt64(), reader.ReadInt64(), reader.ReadInt64());
	}
	if (bitArray[1])
	{
		Rotation = new Vector3(reader.ReadFloat(), reader.ReadFloat(), reader.ReadFloat());
	}
	if (bitArray[2])
	{
		Velocity = new Vector3(reader.ReadFloat(), reader.ReadFloat(), reader.ReadFloat());
	}
	if (bitArray[3])
	{
		Acceleration = new Vector3(reader.ReadFloat(), reader.ReadFloat(), reader.ReadFloat());
	}
	if (bitArray[4])
	{
		ExtraVelocity = new Vector3(reader.ReadFloat(), reader.ReadFloat(), reader.ReadFloat());
	}
	if (bitArray[5])
	{
		LookPitch = reader.ReadFloat();
	}
	if (bitArray[6])
	{
		PhysicsFlags = reader.ReadUInt();
	}
	if (bitArray[7])
	{
		SpeedFlags = reader.ReadByte();
	}
	if (bitArray[8])
	{
		EntityType = reader.ReadUInt();
	}
	if (bitArray[9])
	{
		CurrentMode = reader.ReadByte();
	}
	if (bitArray[10])
	{
		LastShootTime = reader.ReadUInt();
	}
	if (bitArray[11])
	{
		HitCounter = reader.ReadUInt();
	}
	if (bitArray[12])
	{
		LastHitTime = reader.ReadUInt();
	}
	if (bitArray[13])
	{
		appearance.Read(&reader);
	}
	if (bitArray[14])
	{
		Flags1 = reader.ReadByte();
		Flags2 = reader.ReadByte();
	}
	if (bitArray[15])
	{
		RollTime = reader.ReadUInt();
	}
	if (bitArray[16])
	{
		StunTime = reader.ReadInt();
	}
	if (bitArray[17])
	{
		SlowedTime = reader.ReadUInt();
	}
	if (bitArray[18])
	{
		MakeBlueTime = reader.ReadUInt();
	}
	if (bitArray[19])
	{
		SpeedUpTime = reader.ReadUInt();
	}
	if (bitArray[20])
	{
		ShowPatchTime = reader.ReadFloat();
	}
	if (bitArray[21])
	{
		ClassType = reader.ReadByte();
	}
	if (bitArray[22])
	{
		Specialization = reader.ReadByte();
	}
	if (bitArray[23])
	{
		ChargedMP = reader.ReadFloat();
	}
	if (bitArray[24])
	{
		not_used1 = reader.ReadUInt();
		not_used2 = reader.ReadUInt();
		not_used3 = reader.ReadUInt();
	}
	if (bitArray[25])
	{
		not_used4 = reader.ReadUInt();
		not_used5 = reader.ReadUInt();
		not_used6 = reader.ReadUInt();
	}
	if (bitArray[26])
	{
		RayHit = new Vector3 (reader.ReadFloat(),  reader.ReadFloat(), reader.ReadFloat() );
	}
	if (bitArray[27])
	{
		HP = reader.ReadFloat();
	}
	if (bitArray[28])
	{
		MP = reader.ReadFloat();
	}
	if (bitArray[29])
	{
		BlockPower = reader.ReadFloat();
	}
	if (bitArray[30])
	{
		MaxHPMultiplier = reader.ReadFloat();
		ShootSpeed = reader.ReadFloat();
		DamageMultiplier = reader.ReadFloat();
		ArmorMultiplier = reader.ReadFloat();
		ResistanceMultiplier = reader.ReadFloat();
	}
	if (bitArray[31])
	{
		not_used7 = reader.ReadByte();
	}
	if (bitArray[32])
	{
		not_used8 = reader.ReadByte();
	}
	if (bitArray[33])
	{
		Level = reader.ReadUInt();
	}
	if (bitArray[34])
	{
		CurrentXP = reader.ReadUInt();
	}
	if (bitArray[35])
	{
		ParentOwner = reader.ReadUInt64();
	}
	if (bitArray[36])
	{
		unknown_or_not_used1 = reader.ReadUInt();
		unknown_or_not_used2 = reader.ReadUInt();
	}
	if (bitArray[37])
	{
		unknown_or_not_used3 = reader.ReadByte();
	}
	if (bitArray[38])
	{
		unknown_or_not_used4 = reader.ReadUInt();
	}
	if (bitArray[39])
	{
		unknown_or_not_used5 = reader.ReadUInt();
		not_used11 = reader.ReadUInt();
		not_used12 = reader.ReadUInt();
	}
	if (bitArray[40])
	{
		not_used13 = reader.ReadUInt();
		not_used14 = reader.ReadUInt();
		not_used15 = reader.ReadUInt();
		not_used16 = reader.ReadUInt();
		not_used17 = reader.ReadUInt();
		not_used18 = reader.ReadUInt();
	}
	if (bitArray[41])
	{
		not_used20 = reader.ReadUInt();
		not_used21 = reader.ReadUInt();
		not_used22 = reader.ReadUInt();
	}
	if (bitArray[42])
	{
		not_used19 = reader.ReadByte();
	}
	if (bitArray[43])
	{
		ItemData.Read(&reader);
	}
	if (bitArray[44])
	{
		for (int i = 0; i < 13; i++)
		{
			Item item = *new Item();
			item.Read(&reader);
			Equipment[i] = item;
		}
	}
	if (bitArray[45])
	{
		Name = reader.ReadString();
	}
	if (bitArray[46])
	{
		for (int i = 0; i < 11; i++)
		{
			Skills[i] = reader.ReadUInt();
		}
	}
	if (bitArray[47])
	{
		IceBlockFour = reader.ReadUInt();
	}
}


PlayerProfile::~PlayerProfile(void)
{
	/*
	delete LastBitmask;
	delete Position;
	delete Rotation;
	delete Velocity;
	delete Acceleration;
	delete ExtraVelocity;
	delete RayHit;
	delete[] Equipment;
	delete[] Skills;
	*/
}

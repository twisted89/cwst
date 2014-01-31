#include <windows.h>
#include <string>
#include <list>
#include "BinaryReader.h"
#include <bitset>
#include "QVector3.h"
#include "Vector3.h"
#include "Appearance.h"
#include "Item.h"

#pragma once
class PlayerProfile
{
public:
	PlayerProfile(void);
	~PlayerProfile(void);
	void PlayerProfile::Read(BinaryReader br);

	byte * LastBitmask;
	QVector3 * Position;
	Vector3 * Rotation;
	Vector3 * Velocity;
	Vector3 * Acceleration;
	Vector3 * ExtraVelocity;
	float LookPitch;
	unsigned int PhysicsFlags;
	byte SpeedFlags;
	unsigned int EntityType;
	byte CurrentMode;
	unsigned int LastShootTime;
	unsigned int HitCounter;
	unsigned int LastHitTime;
	Appearance appearance;
	byte Flags1;
	byte Flags2;
	unsigned int RollTime;
	int StunTime;
	unsigned int SlowedTime;
	unsigned int MakeBlueTime;
	unsigned int SpeedUpTime;
	float ShowPatchTime;
	byte ClassType;
	byte Specialization;
	float ChargedMP;
	Vector3 * RayHit;
	float HP;
	float MP;
	float BlockPower;
	float MaxHPMultiplier;
	float ShootSpeed;
	float DamageMultiplier;
	float ArmorMultiplier;
	float ResistanceMultiplier;
	unsigned int Level;
	unsigned int CurrentXP;
	Item ItemData;
	Item Equipment[13];
	unsigned int IceBlockFour;
	unsigned int Skills[11];
	std::string Name;

	unsigned int unknown_or_not_used1;
	unsigned int unknown_or_not_used2;
	byte unknown_or_not_used3;
	unsigned int unknown_or_not_used4;
	unsigned int unknown_or_not_used5;
	unsigned int not_used1;
	unsigned int not_used2;
	unsigned int not_used3;
	unsigned int not_used4;
	unsigned int not_used5;
	unsigned int not_used6;
	byte not_used7;
	byte not_used8;
	unsigned __int64 ParentOwner;
	unsigned int not_used11;
	unsigned int not_used12;
	unsigned int not_used13;
	unsigned int not_used14;
	unsigned int not_used15;
	unsigned int not_used16;
	unsigned int not_used17;
	unsigned int not_used18;
	unsigned int not_used20;
	unsigned int not_used21;
	unsigned int not_used22;
	byte not_used19;
};


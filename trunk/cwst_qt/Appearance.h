#include <windows.h>
#include "Vector3.h"
#include "BinaryReader.h"

#pragma once
class Appearance
{
public:
	Appearance(void);
	~Appearance(void);
	void Read(BinaryReader * reader);

	byte NotUsed1, NotUsed2;
	byte HairR, HairG, HairB;
	byte MovementFlags, EntityFlags;
	float Scale;
	float BoundingRadius;
	float BoundingHeight;
	unsigned short HeadModel, HairModel, HandModel, FootModel, BodyModel, BackModel, ShoulderModel, WingModel;
	float HeadScale, BodyScale, HandScale, FootScale, ShoulderScale, WeaponScale, BackScale, Unknown, WingScale;
	float BodyPitch, ArmPitch, ArmRoll, ArmYaw;
	float FeetPitch, WingPitch, BackPitch;
	Vector3 * BodyOffset, * HeadOffset, * HandOffset, * FootOffset, * BackOffset, * WingOffset;
};


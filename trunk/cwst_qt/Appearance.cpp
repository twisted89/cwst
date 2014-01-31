#include "Appearance.h"

void Appearance::Read(BinaryReader * reader)
{
	NotUsed1 = reader->ReadByte();
	NotUsed2 = reader->ReadByte();
	HairR = reader->ReadByte();
	HairG = reader->ReadByte();
	HairB = reader->ReadByte();
	reader->ReadByte(); // skip 1
	MovementFlags = reader->ReadByte();
	EntityFlags = reader->ReadByte();
	Scale = reader->ReadFloat();
	BoundingRadius = reader->ReadFloat();
	BoundingHeight = reader->ReadFloat();
	HeadModel = reader->ReadUInt16();
	HairModel = reader->ReadUInt16();
	HandModel = reader->ReadUInt16();
	FootModel = reader->ReadUInt16();
	BodyModel = reader->ReadUInt16();
	BackModel = reader->ReadUInt16();
	ShoulderModel = reader->ReadUInt16();
	WingModel = reader->ReadUInt16();
	HeadScale = reader->ReadFloat();
	BodyScale = reader->ReadFloat();
	HandScale = reader->ReadFloat();
	FootScale = reader->ReadFloat();
	ShoulderScale = reader->ReadFloat();
	WeaponScale = reader->ReadFloat();
	BackScale = reader->ReadFloat();
	Unknown = reader->ReadFloat();
	WingScale = reader->ReadFloat();
	BodyPitch = reader->ReadFloat();
	ArmPitch = reader->ReadFloat();
	ArmRoll = reader->ReadFloat();
	ArmYaw = reader->ReadFloat();
	FeetPitch = reader->ReadFloat();
	WingPitch = reader->ReadFloat();
	BackPitch = reader->ReadFloat();
	BodyOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
	HeadOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
	HandOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
	FootOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
	BackOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
	WingOffset = new Vector3 (reader->ReadFloat(), reader->ReadFloat(), reader->ReadFloat() );
}

Appearance::Appearance(void)
{
}


Appearance::~Appearance(void)
{
		//delete BodyOffset, HeadOffset, HandOffset, FootOffset, BackOffset, WingOffset;
}

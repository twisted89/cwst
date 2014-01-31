#pragma once
#include <windows.h>
#include <string>
#include <sstream>
class BinaryReader
{
public:
	DWORD BinaryReader::ReadDword();
	byte BinaryReader::ReadByte();
	short BinaryReader::ReadShort();
	std::string BinaryReader::ReadString();
	void BinaryReader::MoveForward(int mf);
	void BinaryReader::MoveTo(int mf);
	int BinaryReader::ReadInt();
	unsigned int BinaryReader::ReadUInt();
	unsigned short BinaryReader::ReadUInt16();
	short BinaryReader::ReadInt16();
	__int64 BinaryReader::ReadInt64();
	float BinaryReader::ReadFloat();
	unsigned __int64 BinaryReader::ReadUInt64();
	byte * BinaryReader::ReadBytes(int count);
	BinaryReader(byte * r);
	~BinaryReader(void);
private:
	byte * reader;
	DWORD Start;
	DWORD End;
};


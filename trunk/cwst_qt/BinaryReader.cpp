#include "BinaryReader.h"

DWORD BinaryReader::ReadDword()
{
	DWORD rdword = *reinterpret_cast<DWORD *>(reader);
	reader += 4;
	return rdword;
}

int BinaryReader::ReadInt()
{
	int rint = *reinterpret_cast<int *>(reader);
	reader += 4;
	return rint;
}

unsigned int BinaryReader::ReadUInt()
{
	unsigned int unint = *reinterpret_cast<unsigned int *>(reader);
	reader += 4;
	return unint;
}

unsigned short BinaryReader::ReadUInt16()
{
	unsigned short unshort = *reinterpret_cast<unsigned short *>(reader);
	reader += 2;
	return unshort;
}

short BinaryReader::ReadInt16()
{
	short rshort = *reinterpret_cast<short *>(reader);
	reader += 2;
	return rshort;
}

__int64 BinaryReader::ReadInt64()
{
	__int64 rint64 = *reinterpret_cast<__int64 *>(reader);
	reader += 8;
	return rint64;
}

byte BinaryReader::ReadByte()
{
	byte rbyte = *reinterpret_cast<byte *>(reader);
	reader++;
	return rbyte;
}

byte * BinaryReader::ReadBytes(int count)
{
	byte * rbyte = new byte[count];
	rbyte = reader;
	reader += count;
	return rbyte;
}

float BinaryReader::ReadFloat()
{
	float rfloat = *reinterpret_cast<float *>(reader);
	reader += 4;
	return rfloat;
}


short BinaryReader::ReadShort()
{
	short rshort = *reinterpret_cast<short *>(reader);
	reader += 2;
	return rshort;
}

unsigned __int64 BinaryReader::ReadUInt64()
{
	short ru64 = *reinterpret_cast<unsigned __int64 *>(reader);
	reader += 8;
	return ru64;
}

std::string BinaryReader::ReadString()
{
	std::string username;
	char character = 1;
	while (character != 0)
	{
		character = *reader;
		username += character;
		reader++;
	}
	return username;
}

void BinaryReader::MoveForward(int mf)
{
	reader += mf;
}

void BinaryReader::MoveTo(int mf)
{
	reader = (byte*)(Start +  mf);
}


BinaryReader::BinaryReader(byte * r)
{
	reader = r;
	Start = (DWORD)reader;
}


BinaryReader::~BinaryReader(void)
{
}

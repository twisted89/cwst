#include <windows.h>
#pragma once
class QVector3
{
public:
	QVector3(INT64 x, INT64 y, INT64 z);
	~QVector3(void);
	INT64 X, Y, Z;
};


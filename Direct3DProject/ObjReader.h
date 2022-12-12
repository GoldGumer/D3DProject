#pragma once

#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

class ObjReader
{
public:
	ObjReader(string objName);
	WORD* GetIndices();
private:
	string objName;

	WORD* indices;

};


#pragma once

#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class CObj : public CModel
{
public:
	CObj();
	~CObj();
	bool load(string path);
};
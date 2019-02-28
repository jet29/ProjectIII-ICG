#pragma once

#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class COff : public CModel
{
public:
	COff();
	~COff();
	bool load(string path);
};
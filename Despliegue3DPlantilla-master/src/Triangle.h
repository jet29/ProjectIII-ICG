#pragma once

#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include "../headers/glm/gtc/quaternion.hpp"
#include "../headers/glm/gtx/quaternion.hpp"
#include "../headers/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <vector>
#include <string>


using std::string;
using std::vector;

class CTriangle
{
protected:

	int vectorIndex[3];
	glm::vec3 triangleVectors[3];
	glm::vec3 normal; 
	glm::vec3 centroid;


public:
	CTriangle(glm::vec3 tv1, glm::vec3 tv2, glm::vec3 tv3, glm::vec3 n, glm::vec3 centroid, int* vI);
	~CTriangle();
	virtual glm::vec3 *getTriangleVectors();
	virtual glm::vec3 getNormal();
	virtual void setTriangleVectors(glm::vec3 *tv);
	virtual void setNormal(glm::vec3 n);
	virtual void setCentroid(glm::vec3 c);
	virtual void setVectorIndex(int v1, int v2, int v3);
	virtual int *getVectorIndex();
	virtual glm::vec3 getCentroid();

};
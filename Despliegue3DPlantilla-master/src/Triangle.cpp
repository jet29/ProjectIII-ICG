#include "Triangle.h"


CTriangle::CTriangle(glm::vec3 tv1, glm::vec3 tv2, glm::vec3 tv3, glm::vec3 n, glm::vec3 c, int* vI) {

	triangleVectors[0] = tv1;
	triangleVectors[1] = tv2;
	triangleVectors[2] = tv3;

	normal = n;

	centroid = c;

	vectorIndex[0] = vI[0];
	vectorIndex[1] = vI[1];
	vectorIndex[2] = vI[2];
}

CTriangle::~CTriangle() {

}

glm::vec3 *CTriangle::getTriangleVectors() {
	return triangleVectors;
}

glm::vec3 CTriangle::getNormal() {
	return normal;
}


void CTriangle::setTriangleVectors(glm::vec3 *tv) {
	triangleVectors[0] = tv[0];
	triangleVectors[1] = tv[1];
	triangleVectors[2] = tv[2];
}

void CTriangle::setNormal(glm::vec3 n) {
	normal = n;
}

void CTriangle::setCentroid(glm::vec3 c) {
	centroid = c;
}

glm::vec3 CTriangle::getCentroid() {
	return centroid;
}

void CTriangle::setVectorIndex(int v1, int v2, int v3) {
	vectorIndex[0] = v1;
	vectorIndex[1] = v2;
	vectorIndex[2] = v3;
}

int *CTriangle::getVectorIndex() {
	return vectorIndex;
}
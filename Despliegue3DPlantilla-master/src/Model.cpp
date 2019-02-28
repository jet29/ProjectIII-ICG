#include "Model.h"

#include <iostream>
using namespace std;

CModel::CModel()
{
	glm::vec3 EulerAngles = glm::vec3(90, 45, 0);
	rotation = glm::quat(EulerAngles);
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	showBoundingBox = false;
	isDisplayNormals = false;
	currentDisplayStyle = filledTriangles;

	colorAmbient[0] = 0;
	colorAmbient[1] = 255;
	colorAmbient[2] = 0;
	colorAmbient[3] = 255;

	colorDiffuse[0] = 255;
	colorDiffuse[1] = 255;
	colorDiffuse[2] = 255;
	colorDiffuse[3] = 255;

	colorSpecular[0] = 255;
	colorSpecular[1] = 255;
	colorSpecular[2] = 255;
	colorSpecular[3] = 255;



	colorBoundingBox = new float[3];
	colorBoundingBox[0] = 0;
	colorBoundingBox[1] = 1;
	colorBoundingBox[2] = 0;

	colorNormal = new float[3];
	colorNormal[0] = 0;
	colorNormal[1] = 0;
	colorNormal[2] = 1;




}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::display()
{

	if (currentDisplayStyle == points) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (currentDisplayStyle == filledTriangles) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (currentDisplayStyle == wireFrame) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	displayNormals();
	displayBoudingBox();


	GLfloat material_ke[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat material_se[] = { 10.0 };

	int a = colorAmbient[0];
	int b = colorAmbient[1];
	int c = colorAmbient[2];
	int d = colorAmbient[3];

	//cout << "a: " << a << ", b:" << b << "c: " << c << "d: " << d << endl;

	float fAmbient[4] = { (float)a / 255.0f , (float)b / 255.0f  , (float)c / 255.0f , (float)d / 255.0f };

	//cout << "ambiente modelo: " << fAmbient[0] << ", " << fAmbient[1] << ", " << fAmbient[2] << ", " << fAmbient[3] << endl;

	a = colorDiffuse[0];
	b = colorDiffuse[1];
	c = colorDiffuse[2];
	d = colorDiffuse[3];

	//cout << "a: " << a << ", b:" << b << "c: " << c << "d: " << d << endl;
	float fDiffuse[4] = { (float)a / 255.0f , (float)b / 255.0f  , (float)c / 255.0f , (float)d / 255.0f };

	//cout << "difuso modelo: " << fDiffuse[0] << ", " << fDiffuse[1] << ", " << fDiffuse[2] << ", " << fDiffuse[3] << endl;

	a = colorSpecular[0];
	b = colorSpecular[1];
	c = colorSpecular[2];
	d = colorSpecular[3];
	//cout << "a: " << a << ", b:" << b << "c: " << c << "d: " << d << endl;
	float fSpecular[4] = { (float)a / 255.0f , (float)b / 255.0f  , (float)c / 255.0f , (float)d / 255.0f };

	//cout << "especular modelo: " << fSpecular[0] << ", " << fSpecular[1] << ", " << fSpecular[2] << ", " << fSpecular[3] << endl;


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_ke);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_se);

	for (int i = 0; i < triangles.size(); i ++)
	{

		//cout << mVertices[i].x << "," << mVertices[i].y << "," <<mVertices[i].z << endl;
		//cout << mVertices[i + 1].x << "," <<mVertices[i + 1].y << " ,"<< mVertices[i + 1].z << endl;
		//cout << mVertices[i + 2].x << "," << mVertices[i + 2].y << " ,"<< mVertices[i + 2].z << endl;

		CTriangle triangle = triangles[i];
		glm::vec3 *triangleVectors = triangle.getTriangleVectors();
		int *triangleIndex = triangle.getVectorIndex();

		glm::vec3 vNormal1 = vectorNormals[triangleIndex[0]];
		glm::vec3 vNormal2 = vectorNormals[triangleIndex[1]];
		glm::vec3 vNormal3 = vectorNormals[triangleIndex[2]];

		glBegin(GL_TRIANGLES);

			glNormal3f(vNormal1.x, vNormal1.y, vNormal1.z);
			glVertex3f(triangleVectors[0].x, triangleVectors[0].y, triangleVectors[0].z);
			glNormal3f(vNormal2.x, vNormal2.y, vNormal2.z);
			glVertex3f(triangleVectors[1].x, triangleVectors[1].y, triangleVectors[1].z);
			glNormal3f(vNormal3.x, vNormal3.y, vNormal3.z);
			glVertex3f(triangleVectors[2].x, triangleVectors[2].y, triangleVectors[2].z);


		glEnd();
	}

	
}

bool CModel::getShowBoundingBox() {
	return showBoundingBox;
}

void CModel::setShowBoundingBox(bool value) {
	showBoundingBox = value;
}


void CModel::displayNormals() {

	if (!isDisplayNormals) return;

	glDisable(GL_LIGHTING);
	//cout << "numero de triangulos: " << triangles.size() << endl;

	glColor3fv(colorNormal);
	
	glBegin(GL_LINES);
		for (int i = 0; i < triangles.size(); i++)
		{
			
			glm::vec3 centroid = triangles[i].getCentroid();

			//cout << "centroide: " << centroid.x << "," <<centroid.y<<","<< centroid.z << endl;
			glm::vec3 normal = triangles[i].getNormal();

			glVertex3f(centroid.x, centroid.y, centroid.z);
			glVertex3f(centroid.x + normal.x, centroid.y + normal.y, centroid.z + normal.z);

			glm::vec3 *vectors = triangles[i].getTriangleVectors();
			int *vecIndex = triangles[i].getVectorIndex();

			glVertex3f(vectorPos[vecIndex[0]].x, vectorPos[vecIndex[0]].y, vectorPos[vecIndex[0]].z);
			glVertex3f(vectorPos[vecIndex[0]].x + vectorNormals[vecIndex[0]].x, vectorPos[vecIndex[0]].y + +vectorNormals[vecIndex[0]].y, vectorPos[vecIndex[0]].z + +vectorNormals[vecIndex[0]].z);

			glVertex3f(vectorPos[vecIndex[1]].x, vectorPos[vecIndex[1]].y, vectorPos[vecIndex[1]].z);
			glVertex3f(vectorPos[vecIndex[1]].x + vectorNormals[vecIndex[1]].x, vectorPos[vecIndex[1]].y + +vectorNormals[vecIndex[1]].y, vectorPos[vecIndex[1]].z + +vectorNormals[vecIndex[1]].z);

			glVertex3f(vectorPos[vecIndex[2]].x, vectorPos[vecIndex[2]].y, vectorPos[vecIndex[2]].z);
			glVertex3f(vectorPos[vecIndex[2]].x + vectorNormals[vecIndex[2]].x, vectorPos[vecIndex[2]].y + +vectorNormals[vecIndex[2]].y, vectorPos[vecIndex[2]].z + +vectorNormals[vecIndex[2]].z);
		
		}

	
	glEnd();

	glEnable(GL_LIGHTING);

}

void CModel::displayBoudingBox() {

	if (!showBoundingBox) return;

	glDisable(GL_LIGHTING);

	glColor3fv(colorBoundingBox);

	float
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;

	min_x = max_x = vectorPos[0].x;
	min_y = max_y = vectorPos[0].y;
	min_z = max_z = vectorPos[0].z;

	for (int i = 0; i < vectorPos.size(); i++)
	{
		if (vectorPos[i].x < min_x) min_x = vectorPos[i].x;
		if (vectorPos[i].x > max_x) max_x = vectorPos[i].x;
		if (vectorPos[i].y < min_y) min_y = vectorPos[i].y;
		if (vectorPos[i].y > max_y) max_y = vectorPos[i].y;
		if (vectorPos[i].z < min_z) min_z = vectorPos[i].z;
		if (vectorPos[i].z > max_z) max_z = vectorPos[i].z;
	}

	glBegin(GL_LINES);

		//abajo

		glVertex3f(min_x, min_y, min_z);
		glVertex3f(min_x, min_y, max_z);

		glVertex3f(min_x, min_y, max_z);
		glVertex3f(max_x, min_y, max_z);

		glVertex3f(max_x, min_y, max_z);
		glVertex3f(max_x, min_y, min_z);

		glVertex3f(max_x, min_y, min_z);
		glVertex3f(min_x, min_y, min_z);

		//arriba

		glVertex3f(min_x, max_y, min_z);
		glVertex3f(min_x, max_y, max_z);

		glVertex3f(min_x, max_y, max_z);
		glVertex3f(max_x, max_y, max_z);

		glVertex3f(max_x, max_y, max_z);
		glVertex3f(max_x, max_y, min_z);

		glVertex3f(max_x, max_y, min_z);
		glVertex3f(min_x, max_y, min_z);

		//lados

		glVertex3f(min_x, max_y, max_z);
		glVertex3f(min_x, min_y, max_z);

		glVertex3f(min_x, max_y, min_z);
		glVertex3f(min_x, min_y, min_z);

		glVertex3f(max_x, max_y, min_z);
		glVertex3f(max_x, min_y, min_z);

		glVertex3f(max_x, max_y, max_z);
		glVertex3f(max_x, min_y, max_z);

	glEnd();

	glEnable(GL_LIGHTING);

}

void CModel::createList() {
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

		glColor4ubv(colorAmbient);
		if (currentDisplayStyle == points) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}
		else if (currentDisplayStyle == filledTriangles) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (currentDisplayStyle == wireFrame) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		for (int i = 0; i < mNumOfVertices; i += 3)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f(mVertices[i + 1].x, mVertices[i + 1].y, mVertices[i + 1].z);
			glVertex3f(mVertices[i + 2].x, mVertices[i + 2].y, mVertices[i + 2].z);
			glEnd();
		}

	glEndList();
}

void CModel::displayList() {
	displayBoudingBox();
	glCallList(list);
}

/*
void CModel::createVBO() {

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &vindex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numOfVertex * 3, vertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* numOfIndex, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CModel::displayVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vindex);
	glDrawElements(GL_TRIANGLES, mNumOfIndex, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}*/

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec3 scale)
{
	mScale = scale;
}

glm::vec3 CModel::getScale()
{
	return mScale;
}


void CModel::setRotationQuat( glm::quat rotationQuat) {
	rotation = rotationQuat;
}

glm::quat CModel::getRotationQuat() {

	return rotation;
}

void CModel::setDisplayStyle(displayStyle ds) {
	currentDisplayStyle = ds;
}


float* CModel::getColorBoundingBox() {
	return colorBoundingBox;
}



void CModel::setColorBoundingBox(float *color) {
	colorBoundingBox[0] = color[0];
	colorBoundingBox[1] = color[1];
	colorBoundingBox[2] = color[2];
}


void CModel::setDisplayNormals(bool state) {
	isDisplayNormals = state;
}

bool CModel::getDisplayNormals() {
	return isDisplayNormals;
}

void CModel::setVectorNormals(){

	glm::vec3 norm = glm::vec3(0,0,0);
	vectorNormals.resize(vectorPos.size());
	for (int i = 0; i < relatedTriangleNormals.size(); i++)
	{
		for (int j = 0; j < relatedTriangleNormals[i].size(); j++) {
			norm += relatedTriangleNormals[i][j];
		}

		vectorNormals[i] = glm::normalize(norm);
		//cout << "normales: " << vectorNormals[i].x << ", " << vectorNormals[i].y << ", " << vectorNormals[i].z << endl;

		norm[0] = 0;
		norm[1] = 0;
		norm[2] = 0;
	}

}


unsigned char* CModel::getAmbientalColor() {
	return colorAmbient;
}


void CModel::setAmbientalColor(unsigned char *color) {

	colorAmbient[0] = color[0];
	colorAmbient[1] = color[1];
	colorAmbient[2] = color[2];
	colorAmbient[3] = color[3];

}

unsigned char* CModel::getDiffuseColor() {
	return colorDiffuse;
}


void CModel::setDiffuseColor(unsigned char *color) {

	colorDiffuse[0] = color[0];
	colorDiffuse[1] = color[1];
	colorDiffuse[2] = color[2];
	colorDiffuse[3] = color[3];

}

unsigned char* CModel::getSpecularColor() {
	return colorSpecular;
}


void CModel::setSpecularColor(unsigned char *color) {

	colorSpecular[0] = color[0];
	colorSpecular[1] = color[1];
	colorSpecular[2] = color[2];
	colorSpecular[3] = color[3];

}

float* CModel::getColorNormal() {
	return colorNormal;
}

void CModel::setColorNormal(float* color) {

	colorNormal[0] = color[0];
	colorNormal[1] = color[1];
	colorNormal[2] = color[2];

}


void  CModel::setAllScale(float scale) {
	allScale = scale;
}


float  CModel::getAllScale() {
	return allScale;
}


#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <string>

using std::string;


//enum displayMode { glBeginEnd, displayList, vertexPointer, vbo } ;
//enum displayStyle { points, wireFrame, filledTriangles } ;
//enum shadingMode { flatShading, gouraudShading } ;



//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;
	glm::vec3 light1Translation;
	glm::vec3 light2Translation;
	glm::vec3 mModelScale;
	float mModelAllScale;

	bool g_isFlatShading;
	bool g_isPerspective;
	bool g_showNormals;
	bool g_showBoundingBox;

	bool g_enableFirstLight;
	bool g_enableSecondLight;

	float mModelColorBoundingBox[3];
	float mModelColorNormal[3];

	unsigned char modelAColor[4] = { 128, 0, 0, 255 }; 
	unsigned char modelDColor[4] = { 255, 255, 0, 255 }; 
	unsigned char modelSColor[4] = { 128, 128, 128, 128 }; 


	unsigned char light1AColor[4] = { 255, 0, 0, 128 };
	unsigned char light1DColor[4] = { 255, 0, 0, 128 };
	unsigned char light1SColor[4] = { 255, 0, 0, 128 };

	unsigned char light2AColor[4] = { 255, 0, 0, 128 };
	unsigned char light2DColor[4] = { 255, 0, 0, 128 };
	unsigned char light2SColor[4] = { 255, 0, 0, 128 };

	float g_Rotation[4];


public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();
	void setModelScale(glm::vec3 modelScale);
	glm::vec3 getModelScale();
	float getAllScale();
	void setAllScale(float scale);
	float *getModelRotation();
	float *getModelColorBoundingBox();
	void setModelColorBoundingBox(float *color);

	float *getModelColorNormal();
	void setModelColorNormal(float *color);
	
	
	void setModelAmbientColor(unsigned char *color);
	unsigned char *getModelAmbientColor();

	void setModelDiffuseColor(unsigned char *color);
	unsigned char *getModelDiffuseColor();

	void setModelSpecularColor(unsigned char *color);
	unsigned char *getModelSpecularColor();

	void setLight1AmbientColor(unsigned char *color);
	unsigned char *getLight1AmbientColor();

	void setLight1DiffuseColor(unsigned char *color);
	unsigned char *getLight1DiffuseColor();

	void setLight1SpecularColor(unsigned char *color);
	unsigned char *getLight1SpecularColor();

	void setLight2AmbientColor(unsigned char *color);
	unsigned char *getLight2AmbientColor();

	void setLight2DiffuseColor(unsigned char *color);
	unsigned char *getLight2DiffuseColor();

	void setLight2SpecularColor(unsigned char *color);
	unsigned char *getLight2SpecularColor();

	void setLight1Translation(float *lightTranslation);
	glm::vec3 getLight1Translation();

	void setLight2Translation(float *lightTranslation);
	glm::vec3 getLight2Translation();


	void setIsPerspective(bool state);
	bool getIsPerspective();

	void setShowNormals(bool state);
	bool getShowNormals();

	void setShowBoundingBox(bool state);
	bool getShowBoundingBox();

	void setIsFlatShading(bool state);
	bool getIsFlatShading();

	void setEnableFirstLight(bool state);
	bool getEnableFirstLight();

	void setEnableSecondLight(bool state);
	bool getEnableSecondLight();





private:
	///Private constructor
	CUserInterface(); 
};
#include "UserInterface.h"

extern int gWidth, gHeight;

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Model");

	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 320'");

	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;

	light1Translation[0] = 0.0f;
	light1Translation[1] = 0.0f;
	light1Translation[2] = 0.0f;

	light2Translation[0] = 0.0f;
	light2Translation[1] = 0.0f;
	light2Translation[2] = 0.0f;

	g_Rotation[0] = 0;
	g_Rotation[1] = 0;
	g_Rotation[2] = 0;
	g_Rotation[3] = 1;

	mModelScale[0] = 1.0f;
	mModelScale[1] = 1.0f;
	mModelScale[2] = 1.0f;

	mModelAllScale = 1.0f;

	mModelColorBoundingBox[0] = 1;
	mModelColorBoundingBox[1] = 1;
	mModelColorBoundingBox[2] = 1;

	mModelColorNormal[0] = 1;
	mModelColorNormal[1] = 1;
	mModelColorNormal[2] = 1;

	g_isFlatShading = false;
	g_isPerspective = true;
	g_showNormals = false;
	g_showBoundingBox = false;
	g_enableFirstLight = true;
	g_enableSecondLight = true;

	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");

	// Add 'g_Rotation' to 'bar': this is a variable of type TW_TYPE_QUAT4F which defines the object's orientation
	TwAddVarRW(mUserInterface, "ObjRotation", TW_TYPE_QUAT4F, &g_Rotation,
		" label='Object rotation' opened=true help='Change the object orientation.' ");

	/*

	TwAddVarRW(mUserInterface, "XSCALE", TW_TYPE_FLOAT, &mModelScale[0], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "YSCALE", TW_TYPE_FLOAT, &mModelScale[1], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "ZSCALE", TW_TYPE_FLOAT, &mModelScale[2], " group='Scale' step=0.01 ");
	TwAddVarRW(mUserInterface, "ALLSCALE", TW_TYPE_FLOAT, &mModelAllScale, " group='Scale' step=0.01 ");


	TwAddVarRW(mUserInterface, "Model Ambient Color", TW_TYPE_COLOR32, &modelAColor," label=' Model Ambient Color' group = 'ModelColor' alpha ");
	TwAddVarRW(mUserInterface, "Model Diffuse Color", TW_TYPE_COLOR32, &modelDColor, " label=' Model Diffuse Color' group = 'ModelColor' alpha");
	TwAddVarRW(mUserInterface, "Model Specular Color", TW_TYPE_COLOR32, &modelSColor, " label=' Model Specular Color' group = 'ModelColor' alpha ");


	TwAddVarRW(mUserInterface, "colorBoundingBox", TW_TYPE_COLOR3F, &mModelColorBoundingBox[0], "label = 'colorBoundingBox' group = 'ModelColor' ");
	TwAddVarRW(mUserInterface, "ColorNormal", TW_TYPE_COLOR3F, &mModelColorNormal[0], "label = 'ColorNormal' group = 'ModelColor' ");



	TwAddVarRW(mUserInterface, "First Light Ambient Color", TW_TYPE_COLOR32, &light1AColor, " label=' First Light Ambient Color' group = 'Firstlight' alpha ");
	TwAddVarRW(mUserInterface, "First Light Diffuse Color", TW_TYPE_COLOR32, &light1DColor, " label=' First Light Diffuse Color' group = 'Firstlight' alpha");
	TwAddVarRW(mUserInterface, "First Light Specular Color", TW_TYPE_COLOR32, &light1SColor, " label=' First Light Specular Color' group = 'Firstlight' alpha ");

	TwAddVarRW(mUserInterface, "X Light1", TW_TYPE_FLOAT, &light1Translation[0], " group='FirstlightTranslation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y Light1", TW_TYPE_FLOAT, &light1Translation[1], " group='FirstlightTranslation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z Light1", TW_TYPE_FLOAT, &light1Translation[2], " group='FirstlightTranslation' step=0.01 ");


	TwAddVarRW(mUserInterface, "Second Light Ambient Color", TW_TYPE_COLOR32, &light2AColor, " label=' Second Light Ambient Color' group = 'SecondLight' alpha ");
	TwAddVarRW(mUserInterface, "Second Light Diffuse Color", TW_TYPE_COLOR32, &light2DColor, " label=' Second Light Diffuse Color' group = 'SecondLight' alpha");
	TwAddVarRW(mUserInterface, "Second Light Specular Color", TW_TYPE_COLOR32, &light2SColor, " label=' Second Light Specular Color' group = 'SecondLight' alpha ");

	TwAddVarRW(mUserInterface, "X Light2", TW_TYPE_FLOAT, &light2Translation[0], " group='SecondLightTranslation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y Light2", TW_TYPE_FLOAT, &light2Translation[1], " group='SecondLightTranslation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z Light2", TW_TYPE_FLOAT, &light2Translation[2], " group='SecondLightTranslation' step=0.01 ");

	//booleanos
	
	TwAddVarRW(mUserInterface, "Flat Shading Mode", TW_TYPE_BOOLCPP, &g_isFlatShading, "group=RenderOptions");
	TwAddVarRW(mUserInterface, "Perspective Mode", TW_TYPE_BOOLCPP, &g_isPerspective, "group=RenderOptions");
	TwAddVarRW(mUserInterface, "Show Bounding Box", TW_TYPE_BOOLCPP, &g_showBoundingBox, "group=RenderOptions ");
	TwAddVarRW(mUserInterface, "Show Normals", TW_TYPE_BOOLCPP, &g_showNormals, "group=RenderOptions");

	TwAddVarRW(mUserInterface, "Enable First Light", TW_TYPE_BOOLCPP, &g_enableFirstLight, "group=RenderOptions");
	TwAddVarRW(mUserInterface, "Enable Second Light", TW_TYPE_BOOLCPP, &g_enableSecondLight, "group=RenderOptions");

	*/

	/*
	
	
	typedef enum { glBeginEnd, displayList, vertexPointer, vbo } displayMode;

	displayMode dMode = glBeginEnd;
	TwEnumVal disMode[] = { {glBeginEnd, "glBeginEnd"}, {displayList, "displayList"}, {vertexPointer, "vertexPointer"}, {vbo, "vbo"} };
	TwType displayModeType = TwDefineEnum("DisplayModeType", disMode, 4);
	TwAddVarRW(mUserInterface, "Display Mode", displayModeType, &dMode, NULL);

	*/

	

	//displayStyle dStyle = points;
	//shadingMode sMode = flatShading;


	//TwType displayModeType;
	//TwType displayStyleType;
	//TwType shadingModeType;



	//displayStyleType = TwDefineEnum("Display Style", NULL, 0);
	//shadingModeType = TwDefineEnum("Shading Mode", NULL, 0);
	// Adding season to bar and defining seasonType enum values
	// This will affect all variables that are of type seasonType.
	//TwAddVarRW(mUserInterface, "Display Style", displayStyleType, &dStyle, " enum='0 {points}, 1 {wireFrame}, 2 {filledTriangles}' ");
	//TwAddVarRW(mUserInterface, "Shading Mode", shadingModeType, &sMode, " enum='0 {flatShading}, 1 {gouraudShading}' ");
	
	
	

	
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setModelTranslation(float *modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

void CUserInterface::setModelScale(glm::vec3 modelScale)
{
	mModelScale[0] = modelScale[0];
	mModelScale[1] = modelScale[1];
	mModelScale[2] = modelScale[2];
}

glm::vec3 CUserInterface::getModelScale()
{
	return mModelScale;
}



void CUserInterface::setModelColorBoundingBox(float *color)
{
	mModelColorBoundingBox[0] = color[0];
	mModelColorBoundingBox[1] = color[1];
	mModelColorBoundingBox[2] = color[2];
}

float* CUserInterface::getModelColorBoundingBox()
{
	return mModelColorBoundingBox;
}


float *CUserInterface::getModelRotation() {
	return g_Rotation;
}


unsigned char* CUserInterface::getModelAmbientColor()
{
	return modelAColor;
}


void CUserInterface::setModelAmbientColor(unsigned char *color)
{
	modelAColor[0] = color[0];
	modelAColor[1] = color[1];
	modelAColor[2] = color[2];
	modelAColor[3] = color[3];

}

unsigned char* CUserInterface::getModelDiffuseColor()
{
	return modelDColor;
}


void CUserInterface::setModelDiffuseColor(unsigned char *color)
{
	modelDColor[0] = color[0];
	modelDColor[1] = color[1];
	modelDColor[2] = color[2];
	modelDColor[3] = color[3];

}

unsigned char* CUserInterface::getModelSpecularColor()
{
	return modelSColor;
}


void CUserInterface::setModelSpecularColor(unsigned char *color)
{
	modelSColor[0] = color[0];
	modelSColor[1] = color[1];
	modelSColor[2] = color[2];
	modelSColor[3] = color[3];

}



float * CUserInterface::getModelColorNormal() {
	return mModelColorNormal;
}

void CUserInterface::setModelColorNormal(float *color) {

	mModelColorNormal[0] = color[0];
	mModelColorNormal[1] = color[1];
	mModelColorNormal[2] = color[2];

}

float CUserInterface::getAllScale() {
	return mModelAllScale;
}


void CUserInterface::setAllScale(float scale) {
	mModelAllScale = scale;
}


void CUserInterface::setIsPerspective(bool state) {

	g_isPerspective = state;

}

bool CUserInterface::getIsPerspective() {

	return g_isPerspective;
}


void CUserInterface::setIsFlatShading(bool state) {

	g_isFlatShading = state;

}

bool CUserInterface::getIsFlatShading() {

	return g_isFlatShading;
}


void CUserInterface::setShowNormals(bool state) {

	g_showNormals = state;
}

bool CUserInterface::getShowNormals() {

	return g_showNormals;
}


void CUserInterface::setShowBoundingBox(bool state) {

	g_showBoundingBox = state;
}

bool CUserInterface::getShowBoundingBox(){

	return g_showBoundingBox;

}


void CUserInterface::setLight1AmbientColor(unsigned char *color) {

	light1AColor[0] = color[0];
	light1AColor[1] = color[1];
	light1AColor[2] = color[2];
	light1AColor[3] = color[3];

}
unsigned char *CUserInterface::getLight1AmbientColor() {
	return light1AColor;
}

void CUserInterface::setLight1DiffuseColor(unsigned char *color) {
	light1DColor[0] = color[0];
	light1DColor[1] = color[1];
	light1DColor[2] = color[2];
	light1DColor[3] = color[3];
}
unsigned char *CUserInterface::getLight1DiffuseColor() {
	return light1DColor;
}

void CUserInterface::setLight1SpecularColor(unsigned char *color) {

	light1SColor[0] = color[0];
	light1SColor[1] = color[1];
	light1SColor[2] = color[2];
	light1SColor[3] = color[3];

}
unsigned char *CUserInterface::getLight1SpecularColor() {
	return light1SColor;
}

//
void CUserInterface::setLight2AmbientColor(unsigned char *color) {

	light2AColor[0] = color[0];
	light2AColor[1] = color[1];
	light2AColor[2] = color[2];
	light2AColor[3] = color[3];
}
unsigned char *CUserInterface::getLight2AmbientColor() {
	return light2AColor;
}

void CUserInterface::setLight2DiffuseColor(unsigned char *color) {
	light2DColor[0] = color[0];
	light2DColor[1] = color[1];
	light2DColor[2] = color[2];
	light2DColor[3] = color[3];
}
unsigned char *CUserInterface::getLight2DiffuseColor() {
	return light2DColor;
}

void CUserInterface::setLight2SpecularColor(unsigned char *color) {

	light2SColor[0] = color[0];
	light2SColor[1] = color[1];
	light2SColor[2] = color[2];
	light2SColor[3] = color[3];
}
unsigned char *CUserInterface::getLight2SpecularColor() {
	return light2SColor;
}

void CUserInterface::setLight1Translation(float *lightTranslation) {
	light1Translation[0] = lightTranslation[0];
	light1Translation[1] = lightTranslation[1];
	light1Translation[2] = lightTranslation[2];
}
glm::vec3 CUserInterface::getLight1Translation() {
	return light1Translation;
}

void CUserInterface::setLight2Translation(float *lightTranslation) {
	light2Translation[0] = lightTranslation[0];
	light2Translation[1] = lightTranslation[1];
	light2Translation[2] = lightTranslation[2];
}
glm::vec3 CUserInterface::getLight2Translation() {
	return light2Translation;
}


void CUserInterface::setEnableFirstLight(bool state){
	
	g_enableFirstLight = state;
}

bool  CUserInterface::getEnableFirstLight() {
	return g_enableFirstLight;
}

void  CUserInterface::setEnableSecondLight(bool state) {
	g_enableSecondLight = state;
}

bool  CUserInterface::getEnableSecondLight() {
	return g_enableSecondLight;
}

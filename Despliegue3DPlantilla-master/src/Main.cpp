#include <Windows.h>
#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "COff.h"
#include "CObj.h"
#include "UserInterface.h"
#include <iostream>

using namespace std;
using std::vector;

enum displayMode { glBeginEnd, displayList, vertexPointer, vbo};

displayStyle currentDisplayStyle = points;
displayMode currentDisplayMode = glBeginEnd;
GLFWwindow *gWindow;
bool isFlat_shading;
bool isPerspective;
bool enableFirstLight;
bool enableSecondLight;
int indexLight1;
int indexLight2;

glm::vec3 moveDir;
glm::quat cameraRot; 
glm::vec3 lookAt = glm::vec3(3.0f, 3.0f, 10.0f);

int gWidth, gHeight;
CUserInterface * userInterface;
vector <CModel *> models;
int picked = -1;

// Intialise and set lighting parameters
GLfloat light1_pos[] = { 0, 0, 0, 1 };
GLfloat light1_ka[] = { 0.2, 0.2, 0.2, 1 };
GLfloat light1_kd[] = { 0, 1.0, 1.0, 1 };
GLfloat light1_ks[] = { 0, 1.0, 1.0, 1 };

GLfloat light2_pos[] = { 0, 0, 0, 1 };
GLfloat light2_ka[] = { 0.2, 0.2, 0.2, 1 };
GLfloat light2_kd[] = { 0, 1.0, 1.0, 1 };
GLfloat light2_ks[] = { 0, 1.0, 1.0, 1 };


bool loadOff(string fileName) {

	COff* off = new COff();

	if (!off->load(fileName))
		return false;

	models.push_back(off);

	if (currentDisplayMode == displayList) off->createList();

	//picked = models.size() - 1;

	return true;

}

bool loadObj(string fileName) {
	CObj* obj = new CObj();

	if (!obj->load(fileName))
		return false;


	models.push_back(obj);

	if (currentDisplayMode == displayList) obj->createList();

	//picked = models.size() - 1;

	return true;
}

string openfilename()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "OBJ Files(.OBJ)\0*.OBJ\0OFF Files(.OFF)\0*.OFF\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

void updateUserInterface()
{
	if (picked > -1) {

		//models[picked]->setTranslation(userInterface->getModelTranslation());

		float* curRotation = userInterface->getModelRotation();
		//cout << "ARRE LOCO 1: "<<curRotation[0] << ", " << curRotation[1] << ", " << curRotation[2] << endl;
		
		cameraRot = glm::quat(curRotation[3], curRotation[0], curRotation[1], curRotation[2]);
		
		
		//cout <<"ARRE LOCO 2: "<< cameraRot.x << ", " << cameraRot.y << ", " << cameraRot.z << endl;
		
		
		//models[picked]->setRotationQuat(cameraRot);


		/*

		models[picked]->setAllScale(userInterface->getAllScale());
		models[picked]->setScale(userInterface->getModelScale());

		models[picked]->setColorBoundingBox(userInterface->getModelColorBoundingBox());
		models[picked]->setColorNormal(userInterface->getModelColorNormal());


		models[picked]->setAmbientalColor(userInterface->getModelAmbientColor());
		models[picked]->setDiffuseColor(userInterface->getModelDiffuseColor());
		models[picked]->setSpecularColor(userInterface->getModelSpecularColor());


		models[picked]->setShowBoundingBox(userInterface->getShowBoundingBox());
		models[picked]->setDisplayNormals(userInterface->getShowNormals());

		*/

		//isPerspective = userInterface->getIsPerspective();

		//isFlat_shading = userInterface->getIsFlatShading();

		//making light things
		unsigned char *light1Acolor = userInterface->getLight1AmbientColor();
		unsigned char *light1Dcolor = userInterface->getLight1DiffuseColor();
		unsigned char *light1Scolor = userInterface->getLight1SpecularColor();

		float a = light1Acolor[0];
		float b = light1Acolor[1];
		float c = light1Acolor[2];
		float d = light1Acolor[3];

		light1_ka[0] = (float)a / 255.0f;
		light1_ka[1] = (float)b / 255.0f;
		light1_ka[2] = (float)c / 255.0f;
		light1_ka[3] = (float)d / 255.0f;

		a = light1Dcolor[0];
		b = light1Dcolor[1];
		c = light1Dcolor[2];
		d = light1Dcolor[3];

		light1_kd[0] = (float)a / 255.0f;
		light1_kd[1] = (float)b / 255.0f;
		light1_kd[2] = (float)c / 255.0f;
		light1_kd[3] = (float)d / 255.0f;

		a = light1Scolor[0];
		b = light1Scolor[1];
		c = light1Scolor[2];
		d = light1Scolor[3];

		light1_ks[0] = (float)a / 255.0f;
		light1_ks[1] = (float)b / 255.0f;
		light1_ks[2] = (float)c / 255.0f;
		light1_ks[3] = (float)d / 255.0f;

		//making light things 2
		unsigned char *light2Acolor = userInterface->getLight2AmbientColor();
		unsigned char *light2Dcolor = userInterface->getLight2DiffuseColor();
		unsigned char *light2Scolor = userInterface->getLight2SpecularColor();

		a = light2Acolor[0];
		b = light2Acolor[1];
		c = light2Acolor[2];
		d = light2Acolor[3];

		light2_ka[0] = (float)a / 255.0f;
		light2_ka[1] = (float)b / 255.0f;
		light2_ka[2] = (float)c / 255.0f;
		light2_ka[3] = (float)d / 255.0f;

		a = light2Dcolor[0];
		b = light2Dcolor[1];
		c = light2Dcolor[2];
		d = light2Dcolor[3];

		light2_kd[0] = (float)a / 255.0f;
		light2_kd[1] = (float)b / 255.0f;
		light2_kd[2] = (float)c / 255.0f;
		light2_kd[3] = (float)d / 255.0f;

		a = light2Scolor[0];
		b = light2Scolor[1];
		c = light2Scolor[2];
		d = light2Scolor[3];

		light2_ks[0] = (float)a / 255.0f;
		light2_ks[1] = (float)b / 255.0f;
		light2_ks[2] = (float)c / 255.0f;
		light2_ks[3] = (float)d / 255.0f;


		glm::vec3 light1Pos = userInterface->getLight1Translation();

		light1_pos[0] = light1Pos[0];
		light1_pos[1] = light1Pos[1];
		light1_pos[2] = light1Pos[2];

		glm::vec3 light2Pos = userInterface->getLight2Translation();

		light2_pos[0] = light2Pos[0];
		light2_pos[1] = light2Pos[1];
		light2_pos[2] = light2Pos[2];

		enableFirstLight = userInterface->getEnableFirstLight();
		enableSecondLight = userInterface->getEnableSecondLight();
	}
}

void displayLights() {

	glLightfv(GL_LIGHT0, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_ks);

	glLightfv(GL_LIGHT1, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light2_ka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light2_kd);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light2_ks);

	/*
	glm::vec3 lightPos = glm::vec3(light1_pos[0], light1_pos[1], light1_pos[2]);
	//cout << "luz 1: " << light1_pos[0] << ", " << light1_pos[1] << "," << light1_pos[2] << endl;
	models[0]->setTranslation(lightPos);
	lightPos = glm::vec3(light2_pos[0], light2_pos[1], light2_pos[2]);
	//cout<<"luz 2: "<< light2_pos[0]<<", "<<light2_pos[1]<<","<< light2_pos[2]<<endl;
	models[1]->setTranslation(lightPos);
	*/

	if (!enableFirstLight) glDisable(GL_LIGHT0);
	else glEnable(GL_LIGHT0);

	if (!enableSecondLight) glDisable(GL_LIGHT1);
	else glEnable(GL_LIGHT1);

}

void display()
{


	if (isFlat_shading) {
		glShadeModel(GL_FLAT);
	}
	else {
		glShadeModel(GL_SMOOTH);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	displayLights();

	//cout << "tamanio modelos: " << models.size() << endl;
	for (unsigned int i = 0; i < models.size(); i++)
	{	

		glm::vec3 translation = models[i]->getTranslation();

		translation += moveDir;
	
		models[i]->setTranslation(translation);

		glm::vec3 scale = models[i]->getScale();
		float modelAllScale = models[i]->getAllScale();

		glPushMatrix();
		
			glm::mat4 rotationMat = glm::toMat4(cameraRot);
			glMultMatrixf(glm::value_ptr(rotationMat));
			glTranslatef(translation.x, translation.y, translation.z);
			glScalef(scale.x + (modelAllScale - 1), scale.y + (modelAllScale - 1), scale.z + (modelAllScale - 1));
			
			
			switch (currentDisplayMode)
			{
			case glBeginEnd:
				models[i]->display();

				break;

			case displayList:
				models[i]->displayList();
				
			default:
				break;
			}

			
		glPopMatrix();
	}
		
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

		float fov = 10.0;
		float Oleft = -1.0, Oright = 1.0, Obottom = -1.0, Otop = 1.0;

		if (isPerspective)
			gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);
		else
			glOrtho(Oleft, Oright, Obottom, Otop, 0.1, 50);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(10, 7, 10, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		string fileName;
		string s = fileName;
		string delimiter = ".";
		size_t pos = 0;
		string token;

		float magnitude = cameraRot.length();
		glm::vec3 normalizedCameraRot = glm::vec3(cameraRot.x / magnitude, cameraRot.y / magnitude, cameraRot.z / magnitude);

		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			case GLFW_KEY_W:
				if (picked > -1) {
					models[picked]->setDisplayStyle(wireFrame);
				}
				break;
			case GLFW_KEY_P:
				if (picked > -1) {
					models[picked]->setDisplayStyle(points);
				}
				break;
			case GLFW_KEY_F:
				if (picked > -1) {
					models[picked]->setDisplayStyle(filledTriangles);
				}
				break;


			case GLFW_KEY_L:

				fileName = openfilename();
				s = fileName;

				cout << fileName << endl;

				delimiter = ".";

				pos = 0;
				
				while ((pos = s.find(delimiter)) != std::string::npos) {
					token = s.substr(0, pos);
					std::cout << token << std::endl;
					s.erase(0, pos + delimiter.length());
				}
				std::cout << s << std::endl;

				if (s.compare("obj") == 0) {
					loadObj(fileName);
				}
				else if (s.compare("off") == 0)
				{
					loadOff(fileName);
				}

				break;

			case GLFW_KEY_UP:

				moveDir = glm::vec3(0, 0, 1.0f);
				break;
			case GLFW_KEY_LEFT:

				moveDir = glm::vec3(1.0f, 0, 0);
				break;
			case GLFW_KEY_DOWN:

				moveDir = glm::vec3(0, 0, -1.0f);
				break;
			case GLFW_KEY_RIGHT:

				moveDir = glm::vec3(-1.0f, 0, 0);
				break;


		}
	}
	else if (action == GLFW_RELEASE) {

		moveDir = glm::vec3(0, 0, 0);
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 2", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

bool initScene()
{
	/*
	CObj* obj = new CObj();

	if (!obj->load("../files/sphere.obj"))
		return false;

	obj->setShowBoundingBox(false);
	obj->setDisplayNormals(false);
	models.push_back(obj);
	indexLight1 = 0;
	if (currentDisplayMode == displayList) obj->createList();

	obj = new CObj();

	if (!obj->load("../files/sphere.obj"))
		return false;

	obj->setShowBoundingBox(false);
	obj->setDisplayNormals(false);
	models.push_back(obj);
	indexLight1 = 0;
	if (currentDisplayMode == displayList) obj->createList();

	cout << "models size " << models.size() << endl;

	*/

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//set the global lighting / shading params
	glLightfv(GL_LIGHT0, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_ks);

	glEnable(GL_LIGHT1);

	//set the global lighting / shading params
	glLightfv(GL_LIGHT1, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light2_ka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light2_kd);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light2_ks);

	// Enable Z-buffering
	glEnable(GL_DEPTH_TEST);



	return true;
}



int main(void)
{


	gWidth = 1200;
	gHeight = 680;
	picked = 1;
	isPerspective = true;

	if (!initGlfw() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;

	glEnable(GL_DEPTH_TEST);

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}
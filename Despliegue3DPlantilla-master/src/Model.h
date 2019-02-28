#pragma once

#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include "../headers/glm/gtc/quaternion.hpp"
#include "../headers/glm/gtx/quaternion.hpp"
#include "../headers/glm/gtc/type_ptr.hpp"
#include "Triangle.h"
#include <iostream>
#include <vector>
#include <string>
//#include "../headers/GL/glew.h"

using std::string;
using std::vector;

enum displayStyle { points, wireFrame, filledTriangles };

class CModel
{
	protected:
		displayStyle currentDisplayStyle;
		vector<CTriangle> triangles;
		vector<glm::vec3> mVertices;
		vector<glm::vec3> vectorPos; //almacena la posicion de los vectores
		vector<glm::vec3> vectorNormals;

		//vector<int> indexVectorForNormals;
		vector< vector<glm::vec3> > relatedTriangleNormals;

		glm::quat rotation;
		glm::vec3 mTranslation;
		glm::vec3 mScale;
		float allScale;
		GLuint list;
		bool showBoundingBox;
		bool isDisplayNormals;
		int mNumOfVertices;
		int mNumOfFaces;


		unsigned char colorAmbient[4];
		unsigned char colorDiffuse[4];
		unsigned char colorSpecular[4];

		float *colorBoundingBox;
		float *colorNormal;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		virtual void createList();
		virtual void displayList();
		virtual void displayBoudingBox();
		virtual bool getShowBoundingBox();
		virtual void setDisplayNormals(bool state);
		virtual bool getDisplayNormals();
		virtual void setShowBoundingBox(bool value);
		virtual void displayNormals();
		virtual void setDisplayStyle(displayStyle ds);

		virtual float* getColorBoundingBox();
		virtual void setColorBoundingBox(float *color);

		virtual float* getColorNormal();
		virtual void setColorNormal(float *color);

		virtual void setVectorNormals();

		virtual void setAmbientalColor(unsigned char *color);
		virtual unsigned char* getAmbientalColor();

		virtual void setDiffuseColor(unsigned char *color);
		virtual unsigned char* getDiffuseColor();

		virtual void setSpecularColor(unsigned char *color);
		virtual unsigned char* getSpecularColor();

		virtual void setAllScale(float scale);
		virtual float getAllScale();
		
		
		//virtual void createVBO();
		//virtual void displayVBO();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();

		void setScale(glm::vec3 scale);
		glm::vec3 getScale();

		void setRotationQuat(glm::quat rotationQuat);
		glm::quat getRotationQuat();

};
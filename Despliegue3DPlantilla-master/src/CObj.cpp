#include "CObj.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


using std::vector;

CObj::CObj()
{
}

CObj::~CObj()
{
}

bool CObj::load(string path)
{
	fstream file;
	string token, v1, v2, v3;
	vector<int> facePos;

	file.open(path, std::ios::in);

	file >> token;

	while (!file.eof()) {


		if (token[0] == '#') {

			file.ignore(100, '\n');
		}
		else if (token.compare("v") == 0) {
			file >> v1;
			file >> v2;
			file >> v3;

			//cout << "v : " << v1 << ", " << v2 << ", " << v3 << endl;

			vectorPos.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
		}
		else if (token.compare("f") == 0) {

			std::string delimiter = "/";
			size_t pos = 0;

			/*

			while ((pos = token.find(delimiter)) != std::string::npos) {
				token2 = token.substr(0, pos);
				std::cout << token2 << std::endl;
				token.erase(0, pos + delimiter.length());
			}

			*/

			file >> token;
			while (token.compare("f") != 0 && token.compare("v") != 0 && token.compare("vn") != 0 && token.compare("s") != 0 && token.compare("vt") && token[0] != '#' && token[0] != 'u' && token.compare("g") != 0 &&!file.eof()) {
				
				pos = token.find(delimiter);
				string face = token.substr(0, pos);
				facePos.push_back(atoi(face.c_str()));

				file >> token;

			}

			for (int i = 1; i < facePos.size() - 1; i++)
			{

				//cout << vectorPos.size() << " ," << facePos[0] - 1 << ", " << facePos[i] - 1 << ", " << facePos[i + 1] - 1 << endl;

				if ((facePos[0] - 1) > vectorPos.size()) {

					vectorPos.resize(facePos[0] - 1);
				}

				if ((facePos[i] - 1) > vectorPos.size()) {

					vectorPos.resize(facePos[i] - 1);
				}

				if ((facePos[i+1] - 1) > vectorPos.size()) {

					vectorPos.resize(facePos[i+1] - 1);
				}

				relatedTriangleNormals.resize(vectorPos.size());

				glm::vec3 v1 = vectorPos[facePos[0] - 1];
				glm::vec3 v2 = vectorPos[facePos[i] - 1];
				glm::vec3 v3 = vectorPos[facePos[i + 1] - 1];

				mVertices.push_back(v1);
				mVertices.push_back(v2);
				mVertices.push_back(v3);

				glm::vec3 edge2 = v2 - v1;
				glm::vec3 edge1 = v2 - v3;
				glm::vec3 triangleNormal = glm::normalize(glm::cross(edge1, edge2));
				glm::vec3 triangleCentroid = glm::vec3((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);

				relatedTriangleNormals[facePos[0] - 1].push_back(triangleNormal);
				relatedTriangleNormals[facePos[i] - 1].push_back(triangleNormal);
				relatedTriangleNormals[facePos[i + 1] - 1].push_back(triangleNormal);

				int vectorIndex[3] = { facePos[0] - 1 , facePos[i] - 1, facePos[i+1] - 1 };
				triangles.push_back(CTriangle(v1, v2, v3, triangleNormal, triangleCentroid, vectorIndex));
			}
			

			facePos.clear();
			continue;
			
		}
		else {
			file.ignore(100, '\n');
		}

		file >> token;
	}
	
	cout << "asdasd" << endl;
	relatedTriangleNormals.resize(vectorPos.size());
	setVectorNormals();
	mNumOfVertices = mVertices.size();

	file.close();
	return true;
}
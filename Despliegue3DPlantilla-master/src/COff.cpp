#include "COff.h"
#include "Triangle.h"
#include <iostream>
using namespace std;

COff::COff()
{
}

COff::~COff()
{
}

bool COff::load(string path)
{
	fstream file;
	string token, v1, v2, v3;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "OFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;

		while (token[0] == '#') {
			//cout << "el super token: " << token.c_str() << endl;
			file.ignore(100, '\n');
			file >> token;
		}

		mNumOfVertices = atoi(token.c_str());


		//cout << "numero de vertices" << token.c_str() << endl;

		file >> token;
		mNumOfFaces = atoi(token.c_str());

		file >> token;


		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> v1;
			file >> v2;
			file >> v3;

			//cout << v1 << ", " << v2 << ", " << v3 << endl;
			vectorPos.push_back(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
		}

		relatedTriangleNormals.resize(vectorPos.size());

		for (int i = 0; i < mNumOfFaces; i++)
		{
			
			file >> token;
			int numVertexFace = atoi(token.c_str());
			int *vertex = new int[numVertexFace];



			for (int i = 0; i < numVertexFace; i++)
			{
				file >> token;
				vertex[i] = atoi(token.c_str());
			}
			
			//cout << vertex[0] << ", " << vertex[1] << ", " << vertex[2] << ", " << vertex[3] << endl;

			for (int i = 1; i < numVertexFace - 1; i++)
			{

				glm::vec3 v1 = vectorPos[vertex[0]];
				glm::vec3 v2 = vectorPos[vertex[i]];
				glm::vec3 v3 = vectorPos[vertex[i+1]];

				mVertices.push_back(v1);
				mVertices.push_back(v2);
				mVertices.push_back(v3);

				glm::vec3 edge2 = vectorPos[vertex[i]] - vectorPos[vertex[0]];
				glm::vec3 edge1 = vectorPos[vertex[i]] - vectorPos[vertex[i+1]];
				glm::vec3 triangleNormal = glm::normalize(glm::cross(edge1, edge2));
				glm::vec3 triangleCentroid = glm::vec3((v1.x + v2.x + v3.x) / 3, (v1.y + v2.y + v3.y) / 3, (v1.z + v2.z + v3.z) / 3);
				
				relatedTriangleNormals[vertex[0]].push_back(triangleNormal);
				relatedTriangleNormals[vertex[i]].push_back(triangleNormal);
				relatedTriangleNormals[vertex[i+1]].push_back(triangleNormal);

				int vectorIndex[3] = { vertex[0], vertex[i], vertex[i + 1]};

				//CTriangle *triangle = new CTriangle(vectorPos[vertex[0]], vectorPos[vertex[0]], vectorPos[vertex[0]], triangleNormal);
				triangles.push_back(CTriangle(v1, v2, v3, triangleNormal, triangleCentroid, vectorIndex));

			}

			file.ignore(100, '\n');

			delete(vertex);

			
		}

		mNumOfVertices = mVertices.size(); //esto todavia se esta pensando si dejar asi



		setVectorNormals();
		file.close();
		return true;
	}
}
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Vector2.h"
#include "Vector3.h"
#include "FaceData.h"

using namespace std;

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	bool LoadFromFile(string fileName);
	vector<Vector3> GetVertices();
	vector<Vector3> GetNormals();
	vector<Vector2> GetTextureCoords();
	vector<FaceData> GetFaces();
private:
	vector<string> splitByChar(string line, char separator);

	bool parse(string content);
	bool parseVertices(string line);
	bool parseTextureCoordinates(string line);
	bool parseNormals(string line);
	bool parseFaces(string line);

	vector<Vector3> verticesData;
	vector<Vector3> normalsData;
	vector<Vector2> texturesData;
	vector<FaceData> facesData;
};
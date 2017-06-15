#include "OBJLoader.h"

OBJLoader::OBJLoader()
{
	vector<string> test = splitByChar("ala ma 1/1 i kot ma    a/2", 'a');
}

OBJLoader::~OBJLoader()
{

}

bool OBJLoader::LoadFromFile(string fileName)
{
	fstream file(fileName);
	if (!file.is_open())
		return false;

	string line;
	string content;
	while (std::getline(file, line))
	{
		if (line != "\n")
			content += (line + '\n');
	}

	return parse(content);
}

vector<Vector3> OBJLoader::GetVertices()
{
	return verticesData;
}

vector<Vector3> OBJLoader::GetNormals()
{
	return normalsData;
}

vector<Vector2> OBJLoader::GetTextureCoords()
{
	return texturesData;
}

vector<FaceData> OBJLoader::GetFaces()
{
	return facesData;
}

bool OBJLoader::parse(string content)
{
	vector<string> tokens = splitByChar(content, '\n');
	for (int i = 0; i < tokens.size(); i++)
	{
		string line = tokens[i];
		char lineType = line[0];
		char lineSubType = line[1];

		switch (lineType)
		{
			case('#'):
			{
				break;
			}
			case('v'):
			{
				bool result;
				if (lineSubType == 't')
					result = parseTextureCoordinates(line);
				else if (lineSubType == 'n')
					result = parseNormals(line);
				else
					result = parseVertices(line);

				if (!result)
				{
					verticesData.clear();
					normalsData.clear();
					texturesData.clear();
					facesData.clear();

					return false;
				}
				break;
			}
			case('f'):
			{
				parseFaces(line);
				break;
			}
		}
	}

	return true;
}

bool OBJLoader::parseVertices(string line)
{
	vector<string> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	char *e;

	Vector3 vData;
	vData.X = strtod(tokens[1].c_str(), &e);
	vData.Y = strtod(tokens[2].c_str(), &e);
	vData.Z = strtod(tokens[3].c_str(), &e);

	verticesData.push_back(vData);
	return true;
}

bool OBJLoader::parseTextureCoordinates(string line)
{
	vector<string> tokens = splitByChar(line, ' ');
	if (tokens.size() < 3)
		return false;

	char *e;

	Vector2 vData;
	vData.X = strtod(tokens[1].c_str(), &e);
	vData.Y = strtod(tokens[2].c_str(), &e);

	texturesData.push_back(vData);
	return true;
}

bool OBJLoader::parseNormals(string line)
{
	vector<string> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	char *e;

	Vector3 vData;
	vData.X = strtod(tokens[1].c_str(), &e);
	vData.Y = strtod(tokens[2].c_str(), &e);
	vData.Z = strtod(tokens[3].c_str(), &e);

	normalsData.push_back(vData);
	return true;
}

bool OBJLoader::parseFaces(string line)
{
	vector<string> tokens = splitByChar(line, ' ');
	if (tokens.size() < 4)
		return false;

	FaceData fData;
	char *e;

	vector<string> subTokens = splitByChar(tokens[1], '/');
	fData.Vertices.X = strtod(subTokens[0].c_str(), &e);
	fData.Textures.X = strtod(subTokens[1].c_str(), &e);
	fData.Normals.X = strtod(subTokens[2].c_str(), &e);

	subTokens = splitByChar(tokens[2], '/');
	fData.Vertices.Y = strtod(subTokens[0].c_str(), &e);
	fData.Textures.Y = strtod(subTokens[1].c_str(), &e);
	fData.Normals.Y = strtod(subTokens[2].c_str(), &e);

	subTokens = splitByChar(tokens[3], '/');
	fData.Vertices.Z = strtod(subTokens[0].c_str(), &e);
	fData.Textures.Z = strtod(subTokens[1].c_str(), &e);
	fData.Normals.Z = strtod(subTokens[2].c_str(), &e);

	facesData.push_back(fData);
	return true;
}

vector<string> OBJLoader::splitByChar(string line, char separator)
{
	string tmp = "";
	vector<string> result;

	for (int i = 0; i <= line.size(); i++)
	{
		if (line[i] == separator || i == line.size())
		{
			if (tmp != "")
			{
				result.push_back(tmp);
				tmp = "";
			}
		}
		else
			tmp += line[i];
	}

	return result;
}
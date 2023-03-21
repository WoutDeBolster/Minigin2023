#include "BobjReader.h"
#include <fstream>

BobjReader::BobjReader(std::string fileLoc)
	:m_File{ fileLoc }
{
}

void BobjReader::ParseBObjFile(std::vector<Vertex>& vertices, std::vector<VertexNormals>& vertexNormals,
	std::vector<Face>& faces, std::vector<std::string>& commands)
{
	std::ifstream objFile;
	std::string line;
	objFile.open(m_File.c_str(), std::ios::binary);
	if (objFile.is_open())
	{
		while (!objFile.eof())
		{
			std::getline(objFile, line);
			if (line.find("v", 0) == 0)
			{
				char startingLetter{ 'c' };;
				Vertex result{ 0, 0, 0 };
				objFile.read(&startingLetter, sizeof(startingLetter));
				objFile.read((char*)&result, sizeof(result));
				m_Vertices.push_back(result);
			}
			if (line.find("vn", 0) == 0)
			{
				char startingLetter{ 'c' };;
				VertexNormals result{ 0, 0, 0 };
				objFile.read(&startingLetter, sizeof(startingLetter));
				objFile.read((char*)&result, sizeof(result));
				m_VertexNormals.push_back(result);
			}
			if (line.find("f", 0) == 0)
			{
				char startingLetter{ 'c' };;
				Face result{ 0, 0, 0 };
				objFile.read(&startingLetter, sizeof(startingLetter));
				objFile.read((char*)&result, sizeof(result));
				m_Faces.push_back(result);
			}
			if (line.find("#", 0) == 0)
			{
				//char startingLetter{ 'c' };
				//std::string result{ "?" };
				//objFile.read((char*)startingLetter, sizeof(startingLetter));
				//objFile.read((char*)&result, sizeof(line));
				//m_Commands.push_back(result);
			}
		}

		vertices = m_Vertices;
		vertexNormals = m_VertexNormals;
		faces = m_Faces;
		commands = m_Commands;

		m_HasParsed = true;
	}
}

void BobjReader::Writeobj(const std::string& fileName)
{
	if (m_HasParsed)
	{
		if (std::ofstream myOutput{ fileName }; myOutput.is_open())
		{
			for (Vertex vertex : m_Vertices)
			{
				myOutput.write((const char*)"v", sizeof(char));
				myOutput.write((const char*)&vertex.x, sizeof(float) * 3);
				myOutput << "\r\n"; // new line
			}
			for (VertexNormals vertexNormal : m_VertexNormals)
			{
				myOutput.write((const char*)"vn", sizeof(char));
				myOutput.write((const char*)&vertexNormal.x, sizeof(float) * 3);
				myOutput << "\r\n"; // new line
			}
			for (Face face : m_Faces)
			{
				myOutput.write((const char*)"f", sizeof(char));
				myOutput.write((const char*)&face.x, sizeof(float) * 3);
				myOutput << "\r\n"; // new line
			}
			for (std::string command : m_Commands)
			{
				myOutput.write((const char*)"#", sizeof(char));
				myOutput.put(static_cast<char>(command.size()));
				myOutput.write((const char*)&m_Commands, sizeof(command));
				myOutput << "\r\n"; // new line
			}
		}
	}
}

#include "ObjReader.h"
#include <fstream>

ObjReader::ObjReader(std::string fileLoc)
	:m_File{ fileLoc }
{
}

void ObjReader::ParseObjFile(std::vector<Vertex>& vertices, std::vector<VertexNormals>& vertexNormals,
	std::vector<Face>& faces, std::vector<std::string>& commands)
{
	std::ifstream objFile;
	std::string line;
	objFile.open(m_File.c_str());
	if (objFile.is_open())
	{
		while (!objFile.eof())
		{
			std::getline(objFile, line);
			if (line.find("v", 0) == 0)
			{
				GetVertex(line);
			}
			if (line.find("vn", 0) == 0)
			{
				GetVertexNormal(line);
			}
			if (line.find("f", 0) == 0)
			{
				GetFace(line);
			}
			if (line.find("#", 0) == 0)
			{
				GetCommand(line, static_cast<char>(line.size()));
			}
		}

		vertices = m_Vertices;
		vertexNormals = m_VertexNormals;
		faces = m_Faces;
		commands = m_Commands;

		m_HasParsed = true;
	}
}

void ObjReader::WriteBobj(const std::string& fileName)
{
	if (m_HasParsed)
	{
		if (std::ofstream myOutput{ fileName, std::ios::binary }; myOutput.is_open())
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

void ObjReader::GetVertex(const std::string& line)
{
	Vertex result{ 0, 0, 0 };
	// https://www.ibm.com/docs/en/zos/2.3.0?topic=programs-sscanf-read-format-data
	sscanf_s(line.c_str(), "v %f %f %f", &result.x, &result.y, &result.z);

	m_Vertices.push_back(result);
}

void ObjReader::GetVertexNormal(const std::string& line)
{
	VertexNormals result{ 0, 0, 0 };
	sscanf_s(line.c_str(), "v %f %f %f", &result.x, &result.y, &result.z);

	m_VertexNormals.push_back(result);
}

void ObjReader::GetFace(const std::string& line)
{
	Face result{ 0, 0, 0 };
	sscanf_s(line.c_str(), "v %i %i %i", &result.x, &result.y, &result.z);

	m_Faces.push_back(result);
}

void ObjReader::GetCommand(const std::string& line, const char stringSize)
{
	char result[255];
	sscanf_s(line.c_str(), "# %s", result, stringSize);
	result[stringSize] = 0;

	m_Commands.push_back(result);
}

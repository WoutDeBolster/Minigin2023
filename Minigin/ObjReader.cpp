#include "ObjReader.h"
#include <fstream>

//ObjReader::ObjReader(std::string fileLoc)
//	:m_File{ fileLoc }
//{
//}
//
//void ObjReader::ParseObjFile(std::vector<glm::f32vec3>& vertices, std::vector<glm::f32vec3>& faces)
//{
//	std::ifstream objFile;
//	std::string line;
//	objFile.open(m_File.c_str());
//	if (objFile.is_open())
//	{
//		while (!objFile.eof())
//		{
//			std::getline(objFile, line);
//			if (line.find("v", 0) == 0)
//			{
//				GetVertex(line);
//			}
//			if (line.find("f", 0) == 0)
//			{
//				GetFace(line);
//			}
//		}
//
//		vertices = m_Vertices;
//		faces = m_Faces;
//	}
//}
//
//void ObjReader::WriteBobj(const std::string& fileName)
//{
//	if (m_Faces.size() != 0 && m_Vertices.size() != 0)
//	{
//		if (std::ofstream myOutput{ fileName, std::ios::binary }; myOutput.is_open())
//		{
//			for (Vertex vertex : m_Vertices)
//			{
//				myOutput.write((const char*)"v", sizeof(char));
//				myOutput.write((const char*)&vertex.x, sizeof(float) * 3);
//				myOutput << "\r\n"; // new line
//			}
//			for (Face face : m_Faces)
//			{
//				myOutput.write((const char*)"f", sizeof(char));
//				myOutput.write((const char*)&face.x, sizeof(float) * 3);
//				myOutput << "\r\n"; // new line
//			}
//		}
//	}
//}
//
//void ObjReader::GetVertex(const std::string& line)
//{
//	Vertex result{ 0, 0, 0 };
//	// https://www.ibm.com/docs/en/zos/2.3.0?topic=programs-sscanf-read-format-data
//	sscanf_s(line.c_str(), "v %f %f %f", &result.x, &result.y, &result.z);
//
//	m_Vertices.push_back(result);
//}
//
//void ObjReader::GetFace(const std::string& line)
//{
//	Face result{ 0, 0, 0 };
//	// https://www.ibm.com/docs/en/zos/2.3.0?topic=programs-sscanf-read-format-data
//	sscanf_s(line.c_str(), "v %i %i %i", &result.x, &result.y, &result.z);
//
//	m_Faces.push_back(result);
//}
#pragma once
#include <vector>
#include <string>
#include "Structs.h"

class ObjReader
{
public:
	ObjReader(std::string fileLoc);
	~ObjReader() = default;

	ObjReader(const ObjReader&) = delete;
	ObjReader(ObjReader&&) noexcept = delete;
	ObjReader& operator=(const ObjReader&) = delete;
	ObjReader& operator=(ObjReader&&) noexcept = delete;

	void ParseObjFile(std::vector<Vertex>& vertices, std::vector<VertexNormals>& vertexNormals,
		std::vector<Face>& faces, std::vector<std::string>& commands);
	void WriteBobj(const std::string& fileName);

private:
	void GetVertex(const std::string& line);
	void GetVertexNormal(const std::string& line);
	void GetFace(const std::string& line);
	void GetCommand(const std::string& line, const char stringSize);

	std::string m_File;
	bool m_HasParsed = false;

	std::vector<Vertex> m_Vertices;
	std::vector<VertexNormals> m_VertexNormals;
	std::vector<Face> m_Faces;
	std::vector<std::string> m_Commands;
};


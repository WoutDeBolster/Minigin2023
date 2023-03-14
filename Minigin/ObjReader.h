#pragma once
#include <vector>
#include <string>
#include <math.h>

struct Vertex
{
	float x, y, z;
};

struct Face
{
	int x, y, z;
};

class ObjReader
{
public:
	ObjReader(std::string fileLoc);
	~ObjReader() = default;

	ObjReader(const ObjReader&) = delete;
	ObjReader(ObjReader&&) noexcept = delete;
	ObjReader& operator=(const ObjReader&) = delete;
	ObjReader& operator=(ObjReader&&) noexcept = delete;

	void ParseObjFile(std::vector<Vertex>& vertices, std::vector<Face>& faces);

private:
	void GetVertex(const std::string& line);
	void GetFace(const std::string& line);

	std::string m_File;

	std::vector<Vertex> m_Vertices;
	std::vector<Face> m_Faces;
};


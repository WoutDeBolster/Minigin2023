#pragma once
#include <vector>
#include <string>
#include "Structs.h"

class BobjReader
{
public:
	BobjReader(std::string fileLoc);
	~BobjReader() = default;

	BobjReader(const BobjReader&) = delete;
	BobjReader(BobjReader&&) noexcept = delete;
	BobjReader& operator=(const BobjReader&) = delete;
	BobjReader& operator=(BobjReader&&) noexcept = delete;

	void ParseBObjFile(std::vector<Vertex>& vertices, std::vector<VertexNormals>& vertexNormals,
		std::vector<Face>& faces, std::vector<std::string>& commands);
	void Writeobj(const std::string& fileName);

private:

	std::string m_File;
	bool m_HasParsed = false;

	std::vector<Vertex> m_Vertices;
	std::vector<VertexNormals> m_VertexNormals;
	std::vector<Face> m_Faces;
	std::vector<std::string> m_Commands;
};


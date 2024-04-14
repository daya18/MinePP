#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace mpp
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 textureCoordinates;
		glm::vec3 normal;
	};

	class Mesh
	{
	public:
		std::string const & GetName () const;
		std::vector <Vertex> const & GetVertices () const;
		std::vector <uint32_t> const & GetIndices () const;
	
	private:
		std::string name;
		std::vector <Vertex> vertices;
		std::vector <uint32_t> indices;

		friend class Scene;
	};

	class Scene
	{
	public:
		Scene ( std::string const & );
		
		std::vector <Mesh> const & GetMeshes () const;

	private:
		std::vector <Mesh> meshes;

	};



	// Implementation
	inline std::string const & Mesh::GetName () const { return name; }
	inline std::vector <Vertex> const & Mesh::GetVertices () const { return vertices; }
	inline std::vector <uint32_t> const & Mesh::GetIndices () const { return indices; }
	inline std::vector <Mesh> const & Scene::GetMeshes () const { return meshes; }
}
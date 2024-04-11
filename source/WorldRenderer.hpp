#pragma once

#include <string>

#include <glm/glm.hpp>

#include "opengl/Shader.hpp"
#include "opengl/VertexArray.hpp"
#include "opengl/Buffer.hpp"
#include "opengl/Texture.hpp"

namespace mpp
{
	class BlockTypeRegistry;
	class BlockModel;

	class WorldRenderer
	{
	public:
		WorldRenderer ( BlockTypeRegistry const &, BlockModel const & );
		~WorldRenderer ();

		void SetCamera ( Camera const & );
		void AddBlock ( glm::vec2 const & position, std::string const & type );
		void DeleteBlock ( glm::vec2 const & position );

		void Render ();

	private:
		Camera const * camera { nullptr };

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		mpp::Texture texture;
	};
}
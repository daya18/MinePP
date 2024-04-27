#include "WorldCache.hpp"

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockCache.hpp"
#include "Chunk.hpp"

namespace mpp
{
	std::array <glm::vec3, 8> const WorldCache::blockVertices
	{
		// Front plane ( Z+ )
		glm::vec3 { -1.0f, -1.0f, 1.0f }, // 0
		glm::vec3 { -1.0f,  1.0f, 1.0f }, // 1
		glm::vec3 {  1.0f,  1.0f, 1.0f }, // 2
		glm::vec3 {  1.0f, -1.0f, 1.0f }, // 3

		// Back plane ( Z- )
		glm::vec3 { -1.0f, -1.0f, -1.0f }, // 4
		glm::vec3 { -1.0f,  1.0f, -1.0f }, // 5
		glm::vec3 {  1.0f,  1.0f, -1.0f }, // 6
		glm::vec3 {  1.0f, -1.0f, -1.0f }, // 7
	};

	std::unordered_map <Directions, std::array < std::array <uint32_t, 3>, 2 > > WorldCache::blockIndices
	{
		{ Directions::forward,	{ std::array <uint32_t, 3> { 0, 1, 2 }, std::array <uint32_t, 3> { 2, 3, 0 } } },
		{ Directions::back,		{ std::array <uint32_t, 3> { 4, 5, 6 }, std::array <uint32_t, 3> { 6, 7, 4 } } },
		{ Directions::left,		{ std::array <uint32_t, 3> { 0, 1, 5 }, std::array <uint32_t, 3> { 5, 4, 0 } } },
		{ Directions::right,	{ std::array <uint32_t, 3> { 6, 7, 3 }, std::array <uint32_t, 3> { 3, 2, 6 } } },
		{ Directions::up,		{ std::array <uint32_t, 3> { 1, 5, 6 }, std::array <uint32_t, 3> { 6, 2, 1 } } },
		{ Directions::down,		{ std::array <uint32_t, 3> { 4, 0, 3 }, std::array <uint32_t, 3> { 3, 7, 4 } } },
	};

	WorldCache::WorldCache ( BlockCache & blockCache )
	:
		blockCache ( &blockCache ),
		shader ( "shader/Shader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 }, { GL_FLOAT, 2 } } ),
		texture ( blockCache.GetBlockTexture ( "Grass" ) ),
		outlineMask ( "image/block_mask/Outline.png" )
	{
		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,    1, 1,
			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,	   0, 1,
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 0,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 0,
					      
			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,    1, 0,
			-1,  1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 1,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 1,
			 1, -1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 0,    0, 0,

			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,    1, 1,
			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 2,    0, 1,
			-1, -1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 0,
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 0,
			
			 1, -1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 0,
			 1,  1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 2,    1, 1,
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,    0, 1,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 0,
																	       
			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 1,
			-1,  1,  1,   faceTextureSize.x * 0, faceTextureSize.y * 0,    0, 0,
			 1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 0,    1, 0,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 1,
																	       
			 1, -1,  1,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 1,
			-1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 1,
			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,    0, 0,
			 1, -1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 0,    1, 0,

		};

		std::vector <GLuint> indices 
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW ),
		indexBuffer.SetData ( indices, GL_STATIC_DRAW ),

		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );
	}

	WorldCache::~WorldCache ()
	{
	}
}

#include "WorldCache.hpp"

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockCache.hpp"
#include "Chunk.hpp"

namespace mpp
{
	WorldCache::WorldCache ( BlockCache & blockCache )
	:
		blockCache ( &blockCache ),
		shader ( "shader/BatchShader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 }, { GL_FLOAT, 2 } } ),
		texture ( blockCache.GetBlockTexture ( "Grass" ) ),
		outlineMask ( "image/block_mask/Outline.png" )
	{
		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			 0.5f,  0.5f,  0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 2,    1, 1,
			-0.5f,  0.5f,  0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 2,	   0, 1,
			-0.5f, -0.5f,  0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 0,
			 0.5f, -0.5f,  0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 0,
					      
			-0.5f, -0.5f, -0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 0,    1, 0,
			-0.5f,  0.5f, -0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 1,
			 0.5f,  0.5f, -0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 1,
			 0.5f, -0.5f, -0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 0,    0, 0,

			-0.5f,  0.5f,  0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 2,    1, 1,
			-0.5f,  0.5f, -0.5f,   faceTextureSize.x * 0, faceTextureSize.y * 2,    0, 1,
			-0.5f, -0.5f, -0.5f,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 0,
			-0.5f, -0.5f,  0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 0,
			
			 0.5f, -0.5f, -0.5f,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 0,
			 0.5f,  0.5f, -0.5f,   faceTextureSize.x * 3, faceTextureSize.y * 2,    1, 1,
			 0.5f,  0.5f,  0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 2,    0, 1,
			 0.5f, -0.5f,  0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 0,
																	       
			-0.5f,  0.5f, -0.5f,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 1,
			-0.5f,  0.5f,  0.5f,   faceTextureSize.x * 0, faceTextureSize.y * 0,    0, 0,
			 0.5f,  0.5f,  0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 0,    1, 0,
			 0.5f,  0.5f, -0.5f,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 1,
																	       
			 0.5f, -0.5f,  0.5f,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 1,
			-0.5f, -0.5f,  0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 1,
			-0.5f, -0.5f, -0.5f,   faceTextureSize.x * 2, faceTextureSize.y * 0,    0, 0,
			 0.5f, -0.5f, -0.5f,   faceTextureSize.x * 3, faceTextureSize.y * 0,    1, 0,

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

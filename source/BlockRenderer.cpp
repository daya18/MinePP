#include "BlockRenderer.hpp"

#include "Camera.hpp"
#include "Block.hpp"
#include "Scene.hpp"

namespace mpp
{
	BlockRenderer::BlockRenderer ( BlockTypeRegistry const & )
	:
		shader ( "shader/Shader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 }, { GL_FLOAT, 2 } } ),
		texture ( "image/block/Grass.png" ),
		outlineMask ( "image/block_mask/Outline.png" )
	{
		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 0,
			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,	   0, 1,
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,    1, 1,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 0,
					      
			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,    1, 0,
			-1,  1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    1, 1,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    0, 1,
			 1, -1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 0,    0, 0,

			-1, -1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 0,
			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 2,    0, 1,
			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,    1, 1,
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 0,
			
			 1, -1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 0,
			 1,  1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 2,    1, 1,
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,    0, 1,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 0,
																	       
			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,    0, 1,
			-1,  1,  1,   faceTextureSize.x * 0, faceTextureSize.y * 0,    0, 0,
			 1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 0,    1, 0,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,    1, 1,
																	       
			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,    0, 0,
			-1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,    0, 1,
			 1, -1,  1,   faceTextureSize.x * 3, faceTextureSize.y * 1,    1, 1,
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


		//Scene scene { "model/Block.obj" };

		//int indexOffset { 0 };
		//for ( auto const & mesh : scene.GetMeshes () )
		//{
		//	for ( auto const & vertex : mesh.GetVertices () )
		//	{
		//		vertices.push_back ( vertex.position.x );
		//		vertices.push_back ( vertex.position.y );
		//		vertices.push_back ( vertex.position.z );

		//		vertices.push_back ( vertex.textureCoordinates.x );
		//		vertices.push_back ( vertex.textureCoordinates.y );
		//	}

		//	for ( auto const & index : mesh.GetIndices () )
		//		indices.push_back ( indexOffset + index );

		//	indexOffset += mesh.GetVertices ().size ();
		//}

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW ),
		indexBuffer.SetData ( indices, GL_STATIC_DRAW ),

		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );
	}

	BlockRenderer::~BlockRenderer ()
	{
	}
	
	void BlockRenderer::SetCamera ( Camera const & camera )
	{
		this->camera = & camera;
	}

	void BlockRenderer::AddBlock ( Block const & block )
	{
		blocks.push_back ( &block );
	}

	void BlockRenderer::DeleteBlock ( Block const & block )
	{
		std::erase ( blocks, &block );
	}

	void BlockRenderer::Render ()
	{
		//glEnable ( GL_CULL_FACE );

		if ( ! camera ) return;

		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		shader.SetUniform ( "u_viewMatrix", camera->GetViewMatrix () );
		shader.SetUniform ( "u_projectionMatrix", camera->GetProjectionMatrix () );

		shader.SetUniform ( "u_sampler", 0 );
		texture.Bind ( 0 );


		for ( auto const & block : blocks )
		{
			auto transform { block->GetTransform () };
			
			shader.SetUniform ( "u_useMask", block->GetHighlighted () );
			
			if ( block->GetHighlighted () )
			{
				shader.SetUniform ( "u_maskSampler", 1 );
				outlineMask.Bind ( 1 );
			}

			shader.SetUniform ( "u_modelMatrix", transform.GetMatrix () );

			glDrawElements ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
		}
	}
}
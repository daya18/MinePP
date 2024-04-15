#include "BlockThumbnailRenderer.hpp"

namespace mpp
{
	BlockThumbnailRenderer::BlockThumbnailRenderer ()
	:
		shader ( "shader/Shader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } } )
	{
		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,
			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,

			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,
			-1,  1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 1,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,
			 1, -1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 0,

			-1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 2,
			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 2,
			-1, -1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,
			-1, -1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 1,

			 1, -1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 1,
			 1,  1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 2,
			 1,  1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 2,
			 1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,

			-1,  1, -1,   faceTextureSize.x * 0, faceTextureSize.y * 1,
			-1,  1,  1,   faceTextureSize.x * 0, faceTextureSize.y * 0,
			 1,  1,  1,   faceTextureSize.x * 1, faceTextureSize.y * 0,
			 1,  1, -1,   faceTextureSize.x * 1, faceTextureSize.y * 1,

			 1, -1,  1,   faceTextureSize.x * 3, faceTextureSize.y * 1,
			-1, -1,  1,   faceTextureSize.x * 2, faceTextureSize.y * 1,
			-1, -1, -1,   faceTextureSize.x * 2, faceTextureSize.y * 0,
			 1, -1, -1,   faceTextureSize.x * 3, faceTextureSize.y * 0,

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

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW );
		indexBuffer.SetData ( indices, GL_STATIC_DRAW );

		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );
	}

	void BlockThumbnailRenderer::Render ()
	{
	/*	glEnable ( GL_CULL_FACE );

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

		glDisable ( GL_CULL_FACE );*/
	}
}
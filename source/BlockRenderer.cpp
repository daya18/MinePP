#include "BlockRenderer.hpp"

#include "Camera.hpp"
#include "BlockModel.hpp"
#include "Block.hpp"

namespace mpp
{
	BlockRenderer::BlockRenderer ( BlockTypeRegistry const &, BlockModel const & blockModel )
	:
		vertexBuffer ( blockModel.GetRawVertices (), GL_STATIC_DRAW ),
		indexBuffer ( blockModel.GetRawIndices (), GL_STATIC_DRAW ),
		shader ( "shader/Shader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } } ),
		texture ( "image/block/Grass.png" )
	{
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
			shader.SetUniform ( "u_modelMatrix", block->GetTransformMatrix () );
			glDrawElements ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
		}
	}
}
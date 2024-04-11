#include "WorldRenderer.hpp"

#include "Camera.hpp"
#include "BlockModel.hpp"

namespace mpp
{
	WorldRenderer::WorldRenderer ( BlockTypeRegistry const &, BlockModel const & blockModel )
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

	WorldRenderer::~WorldRenderer ()
	{
	}
	
	void WorldRenderer::SetCamera ( Camera const & camera )
	{
		this->camera = & camera;
	}

	void WorldRenderer::AddBlock ( glm::vec2 const & position, std::string const & type )
	{
	}

	void WorldRenderer::DeleteBlock ( glm::vec2 const & position )
	{
	}

	void WorldRenderer::Render ()
	{
		if ( ! camera ) return;

		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		shader.SetUniform ( "u_viewMatrix", camera->GetViewMatrix () );
		shader.SetUniform ( "u_projectionMatrix", camera->GetProjectionMatrix () );

		shader.SetUniform ( "u_sampler", 0 );
		texture.Bind ( 0 );

		glDrawElements ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
	}
}
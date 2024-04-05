#include "World.hpp"

#include "Window.hpp"

namespace mpp
{
	World::World ( Window & window )
	:
		shader ( "shader/Shader.glsl" ),
		vertexBuffer ( std::vector <float> { 0.0f, 10.0, 0.0f, 20.0f, -10.0f, 0.0f, -10.0f, -10.0f, 0.0f }, GL_STATIC_DRAW ),
		vertexArray ( { { GL_FLOAT, 3 } } ),
		camera ( window, { 0.0f, 0.0f, 100.0f } )
	{
	}

	void World::Update ()
	{
		camera.Update ();
	}

	void World::Render ()
	{
		shader.Bind ();
		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );

		shader.SetUniform ( "u_viewMatrix", camera.GetViewMatrix () );
		shader.SetUniform ( "u_projectionMatrix", camera.GetProjectionMatrix () );

		glDrawArrays ( GL_TRIANGLES, 0, 3 );
	}
}


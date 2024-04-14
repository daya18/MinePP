#include "RectangleRenderer.hpp"

#include "../Camera.hpp"
#include "../Window.hpp"

#include "Rectangle.hpp"

namespace mpp
{
	RectangleRenderer::RectangleRenderer ( Window const & window )
	:
		shader ( "shader/GUIShader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 } } )
	{
		SetViewportSize ( window.GetSize () );

		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			 1.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f
		};

		std::vector <GLuint> indices
		{
			0, 1, 2, 2, 3, 0,
		};

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW ),
		indexBuffer.SetData ( indices, GL_STATIC_DRAW ),

		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );
	}

	RectangleRenderer::~RectangleRenderer ()
	{
	}
	
	void RectangleRenderer::AddRectangle ( Rectangle const & rectangle )
	{
		instanceTransformMatrices.push_back ( rectangle.GetTransform ().GetMatrix () );
		rectangles.push_back ( &rectangle );
	}

	void RectangleRenderer::RemoveRectangle ( Rectangle const & rectangle )
	{
		auto rectangleIt { std::find_if ( rectangles.begin (), rectangles.end (), 
			[&rectangle] ( Rectangle const * a ) { return a == &rectangle; } ) };

		instanceTransformMatrices.erase ( instanceTransformMatrices.begin () + std::distance ( rectangles.begin (), rectangleIt ) );
		rectangles.erase ( rectangleIt );
	}

	void RectangleRenderer::SetViewportSize ( glm::vec2 const & size )
	{
		projectionMatrix = glm::ortho <float> ( -size.x * 0.5f, size.x * 0.5f, -size.y * 0.5f, size.y * 0.5f, -1000.0f, 1000.0f );
	}

	void RectangleRenderer::Render ()
	{
		if ( rectangles.empty () )
			return;

		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		shader.SetUniform ( "u_projectionMatrix", projectionMatrix );
		shader.SetUniform ( "u_instanceTransformMatrices", instanceTransformMatrices );

		glDrawElementsInstanced ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceTransformMatrices.size () );
	}
}
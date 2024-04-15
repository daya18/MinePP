#include "RectangleRenderer.hpp"

#include "../Camera.hpp"
#include "../Window.hpp"

#include "Rectangle.hpp"

namespace mpp
{
	RectangleRenderer::RectangleRenderer ( Window & window )
	:
		window ( & window ),
		shader ( "shader/GUIShader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } } ),
		whiteTexture ( "image/White.png" )
	{
		SetViewportSize ( window.GetSize () );

		glm::vec2 faceTextureSize { 1.0f / 3.0f, 1.0f / 2.0f };

		std::vector <float> vertices
		{
			 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 0.0f
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
		rectangles.push_back ( &rectangle );
	}

	void RectangleRenderer::RemoveRectangle ( Rectangle const & rectangle )
	{
		std::erase ( rectangles, &rectangle );
	}

	void RectangleRenderer::SetViewportSize ( glm::vec2 const & size )
	{
		projectionMatrix = glm::ortho <float> ( 
			 0.0f,    size.x, 
			 size.y,  0.0f, 
			-1000.0f, 1000.0f 
		);
	}

	void RectangleRenderer::Render ()
	{
		if ( rectangles.empty () )
			return;

		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		shader.SetUniform ( "u_projectionMatrix", projectionMatrix );
		
		for ( auto rectangle : rectangles )
		{
			shader.SetUniform ( "u_modelMatrix", rectangle->GetTransform().GetMatrix () );
			shader.SetUniform ( "u_color", rectangle->GetColor () );
			shader.SetUniform ( "u_texture", 0 );
			
			( rectangle->GetTexture () ? rectangle->GetTexture () : & whiteTexture )->Bind ( 0 );

			glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
		}
	}

	Texture & RectangleRenderer::GetTexture ( std::string const & name )
	{
		if ( name.empty () )
			return whiteTexture;

		auto textureIt { textures.find ( name ) };
		
		if ( textureIt == textures.end () )
			textureIt = textures.emplace ( name, Texture { name } ).first;

		return textureIt->second;
	}
}
#include "TextRenderer.hpp"

#include "../Window.hpp"
#include "Text.hpp"

namespace mpp
{
	TextRenderer::TextRenderer ( Window & window, std::string const & fontPath )
	:
		shader ( "shader/TextShader.glsl" ),
		vertexArray ( { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } } )
	{
		std::vector <float> vertices
		{
			 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  0.0f,  1.0f, 1.0f
		};

		std::vector <GLuint> indices
		{
			0, 1, 2, 2, 3, 0,
		};

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW );
		indexBuffer.SetData ( indices, GL_STATIC_DRAW );

		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );

		SetViewportSize ( window.GetSize () );

		FTCheckError ( FT_Init_FreeType ( &library ) );
		FTCheckError ( FT_New_Face ( library, fontPath.data (), 0, &face ) );

		FT_Set_Pixel_Sizes ( face, 0, 50 );

		for ( int i { 0 }; i < face->num_glyphs; ++i )
		{
			FT_Load_Glyph ( face, i, FT_LOAD_RENDER );

			Glyph glyph {};
			
			glyph.metrics = face->glyph->metrics;
			glyph.size = { glyph.metrics.width / 64, glyph.metrics.height / 64 };
			glyph.bearing = { glyph.metrics.horiBearingX / 64, glyph.metrics.horiBearingY / 64 };
			glyph.advance = glyph.metrics.horiAdvance / 64;

			glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
			glyph.texture.SetData ( face->glyph->bitmap.buffer, { face->glyph->bitmap.width, face->glyph->bitmap.rows }, GL_RED );

			glyphs.push_back ( glyph );
		}
	}

	TextRenderer::~TextRenderer ()
	{
		FT_Done_FreeType ( library );
	}

	TextRenderer::TextRenderer ( TextRenderer && r )
		: library ( std::exchange ( r.library, nullptr ) )
	{
		throw std::runtime_error { "TextRenderer's move constructor isn't fully implemented" };
	}

	void TextRenderer::FTCheckError ( FT_Error error )
	{
		if ( error != FT_Err_Ok )
			std::cout << "Freetype Error:  " << FT_Error_String ( error ) << std::endl;
	}
	
	void TextRenderer::AddText ( Text const & text )
	{
		texts.push_back ( &text );
	}

	void TextRenderer::RemoveText ( Text const & text )
	{
		std::erase ( texts, & text );
	}

	void TextRenderer::Render ()
	{
		for ( auto text : texts )
		{
			auto glyphs { GetGlyphs ( *text ) };
			
			float maxAscent, maxDescent;
			CalculateMaxAscentDescent ( glyphs, maxAscent, maxDescent );
			float width { CalculateWidth ( glyphs ) };

			maxAscent *= text->transform.GetScale ().y;
			maxDescent *= text->transform.GetScale ().y;
			width *= text->transform.GetScale ().x;

			float height { maxAscent + maxDescent };

			float offset { 0.0f };

			for ( auto & glyph : glyphs )
			{
				glm::vec3 glyphPosition { text->transform.GetPosition () };
				glyphPosition.x += offset + glyph->bearing.x * text->transform.GetScale ().x;
				glyphPosition.y -= glyph->bearing.y * text->transform.GetScale ().x;
				glyphPosition.y += maxAscent;

				// Shift origin
				glyphPosition.x -= width * text->origin.x;
				glyphPosition.y -= height * text->origin.y;

				RenderGlyph ( *glyph, glyphPosition, text->transform.GetScale (), text->color);
				
				offset += glyph->advance * text->transform.GetScale ().x;
			}
		}
	}

	void TextRenderer::SetViewportSize ( glm::vec2 const & size )
	{
		projectionMatrix = glm::ortho <float> (
			0.0f, size.x,
			size.y, 0.0f,
			-1000.0f, 1000.0f
		);
	}

	void TextRenderer::CalculateMaxAscentDescent ( std::vector <Glyph const *> const & glyphs, float & maxAscent, float & maxDescent )
	{
		maxAscent = -std::numeric_limits<float>::infinity ();
		maxDescent = -std::numeric_limits<float>::infinity ();

		for ( auto const & glyph : glyphs )
		{
			maxAscent = glm::max <float> ( maxAscent, glyph->bearing.y );
			maxDescent = glm::max <float> ( maxDescent, glyph->size.y - glyph->bearing.y );
		}
	}
	
	float TextRenderer::CalculateWidth ( std::vector <Glyph const *> const & glyphs )
	{
		float width { 0.0f };

		for ( auto & glyph : glyphs )
			width += glyph->advance;

		return width;
	}

	std::vector <TextRenderer::Glyph const *> TextRenderer::GetGlyphs ( Text text )
	{
		std::vector <Glyph const *> glyphs;
		glyphs.reserve ( text.text.size () );

		for ( auto ch : text.text )
			glyphs.push_back ( & this->glyphs [ FT_Get_Char_Index ( face, ch ) ] );

		return glyphs;
	}

	void TextRenderer::RenderGlyph ( 
		Glyph const & glyph, 
		glm::vec3 const & position, 
		glm::vec2 const & scale, 
		glm::vec4 const & color )
	{
		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );
		

		Transform transform { position, { glyph.size * scale, 1.0f } };
		shader.SetUniform ( "u_modelMatrix", transform.GetMatrix () );

		shader.SetUniform ( "u_projectionMatrix", projectionMatrix );
		shader.SetUniform ( "u_color", color );
		
		shader.SetUniform ( "u_texture", 0 );
		glyph.texture.Bind ( 0 );

		glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
	}
}
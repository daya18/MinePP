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

		vertexBuffer.SetData ( vertices, GL_STATIC_DRAW ),
			indexBuffer.SetData ( indices, GL_STATIC_DRAW ),

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
		TextData textData;

		float maxAscent { -std::numeric_limits<int>::infinity() };
		float maxDescent { -std::numeric_limits<int>::infinity () };
		
		// Get ref to glyph, and calculate max ascent and descent for the text
		for ( auto const & ch : text.GetText () )
		{
			auto const & glyph { glyphs [ FT_Get_Char_Index ( face, ch ) ] };
			textData.glyphDatas.push_back ( TextData::GlyphData { &glyph, {} } );
			maxAscent = glm::max <float> ( maxAscent, glyph.bearing.y );
			maxDescent = glm::max <float> ( maxDescent, glyph.size.y - glyph.bearing.y );	
		}
		
		// Calculate glyph offsets
		glm::vec2 penPosition { 0.0f, maxAscent };
		for ( auto & glyphData : textData.glyphDatas )
		{
			glm::vec2 bitmapPosition { glyphData.glyph->bearing.x, -glyphData.glyph->bearing.y };
			glyphData.transform.SetPosition ( { penPosition + bitmapPosition, 0.0f } );
			penPosition.x += glyphData.glyph->advance;
		}

		// To Do: Fix width being slightly larger than the actual text width
		textData.size = { penPosition.x, maxDescent + maxAscent };

		textDatas.emplace ( & text, textData );
	}

	void TextRenderer::RemoveText ( Text const & text )
	{
		textDatas.erase ( & text );
	}

	void TextRenderer::Render ()
	{
		shader.Bind ();
		vertexArray.Bind ();
		indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		shader.SetUniform ( "u_projectionMatrix", projectionMatrix );

		shader.SetUniform ( "u_color", glm::vec4 { 1.0f, 1.0f, 1.0f, 1.0f } );
		shader.SetUniform ( "u_texture", 0 );

		for ( auto & [ text, textData ] : textDatas )
		{
			for ( auto & glyphData : textData.glyphDatas )
			{
				Transform transform;
				transform.SetPosition ( text->GetTransform().GetPosition () + glyphData.transform.GetPosition () );
				transform.SetScale ( { glyphData.glyph->size, 0.0f } );
				
				glyphData.glyph->texture.Bind ( 0 );

				shader.SetUniform ( "u_modelMatrix", transform.GetMatrix () );

				glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
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
}
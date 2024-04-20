#pragma once

#include "../opengl/Texture.hpp"
#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"

#include "../scene/Transform.hpp"

namespace mpp
{
	class Window;
	class Text;

	class TextRenderer
	{
	public:
		TextRenderer ( Window &, std::string const & fontPath );
		TextRenderer ( TextRenderer const & ) = delete;
		TextRenderer ( TextRenderer && );
		~TextRenderer ();

		TextRenderer & operator = ( TextRenderer const & ) = delete;
		TextRenderer & operator = ( TextRenderer && ) = delete;
		
		void AddText ( Text const & );
		void RemoveText ( Text const & );
		glm::vec2 GetTextSize ( Text const & );

		void Render ();

	private:
		static void FTCheckError ( FT_Error );
		void SetViewportSize ( glm::vec2 const & );

		struct Glyph
		{
			FT_Glyph_Metrics metrics;
			glm::vec2 size;
			glm::vec2 bearing;
			float advance;
			Texture texture;
		};

		struct TextData
		{
			struct GlyphData
			{
				Glyph const * glyph;
				Transform transform;
			};

			glm::vec2 size;
			std::vector <GlyphData> glyphDatas;
		};

		FT_Library library;
		FT_Face face;
		std::vector <Glyph> glyphs;
		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		glm::mat4 projectionMatrix { glm::identity <glm::mat4> () };
		std::unordered_map <Text const *, TextData> textDatas;
	};



	// Implementation
	inline glm::vec2 TextRenderer::GetTextSize ( Text const & text ) { return textDatas.at ( &text ).size; }
}
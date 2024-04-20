#pragma once

#include "../opengl/Texture.hpp"
#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"

#include "../scene/Transform.hpp"

namespace mpp
{
	class Window;
	struct Text;

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

		std::vector <Glyph const *> GetGlyphs ( Text text );
		void CalculateMaxAscentDescent ( std::vector <Glyph const *> const & glyphs, float & ascent, float & descent );
		float CalculateWidth ( std::vector <Glyph const *> const & glyphs );
		void RenderGlyph ( Glyph const &, glm::vec3 const & position, glm::vec2 const & scale, glm::vec4 const & color );

		FT_Library library;
		FT_Face face;
		std::vector <Glyph> glyphs;
		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		glm::mat4 projectionMatrix { glm::identity <glm::mat4> () };
		std::vector <Text const *> texts;
		//std::unordered_map <Text const *, TextData> textDatas;
	};
}
#pragma once

#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"
#include "../opengl/Texture.hpp"

namespace mpp
{
	class Window;
	class Rectangle;
	class Text;

	class RectangleRenderer
	{
	public:
		RectangleRenderer ( Window & window );
		~RectangleRenderer ();

		void AddRectangle ( Rectangle const & );
		void RemoveRectangle ( Rectangle const & );
		
		void Render ();
		Window & GetWindow ();

	private:
		void SetViewportSize ( glm::vec2 const & );
		Texture & GetTexture ( std::string const & );

		Window * window;

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		Texture whiteTexture;
		glm::mat4 projectionMatrix { glm::identity <glm::mat4> () };
		std::vector <Rectangle const *> rectangles;
		std::unordered_map <std::string, Texture> textures;
	};



	// Implementation
	inline Window & RectangleRenderer::GetWindow () { return *window; }
}
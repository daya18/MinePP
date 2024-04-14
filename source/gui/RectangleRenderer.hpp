#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"
#include "../opengl/Texture.hpp"

namespace mpp
{
	class Window;
	class Rectangle;

	class RectangleRenderer
	{
	public:
		RectangleRenderer ( Window const & window );
		~RectangleRenderer ();

		void AddRectangle ( Rectangle const & );
		void RemoveRectangle ( Rectangle const & );

		void Render ();

	private:
		void SetViewportSize ( glm::vec2 const & );
		
		Camera const * camera { nullptr };

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		glm::mat4 projectionMatrix { glm::identity <glm::mat4> () };
		std::vector <glm::mat4> instanceTransformMatrices;
		std::vector <Rectangle const *> rectangles;
	};
}
#pragma once

#include "Camera.hpp"
#include "opengl/Shader.hpp"
#include "opengl/VertexArray.hpp"
#include "opengl/Buffer.hpp"

namespace mpp
{
	class Window;

	class World
	{
	public:
		World ( Window & );

		void Update ();
		void Render ();

	private:
		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::VertexArray vertexArray;
		Camera camera;
	};
}
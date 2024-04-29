#pragma once

#include "../../opengl/Buffer.hpp"

namespace mpp
{
	class Block;
	class Shader;
	class Texture;

	class Batch
	{
	public:
		Batch ( Texture const & texture, std::vector <Block *> const & blocks );

		void Render ( Shader & );

	private:
		int instanceCount { 0 };
		Buffer uniformBuffer;
		Texture const * texture;
	};
}
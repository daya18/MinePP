#pragma once

#include "Camera.hpp"
#include "BlockRenderer.hpp"
#include "Block.hpp"

namespace mpp
{
	class Window;

	class World
	{
	public:
		World ( Window &, BlockTypeRegistry const &, BlockModel const & );

		void Update ();
		void Render ();
		void CreateBlock ( std::string const &, glm::vec3 const & );

	private:
		Camera camera;
		BlockRenderer blockRenderer;
		std::list <Block> blocks;
	};
}
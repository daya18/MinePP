#pragma once

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockRenderer.hpp"
#include "BlockRayCaster.hpp"

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
		std::list <Block> blocks;
		BlockRenderer blockRenderer;
		BlockRayCaster blockRayCaster;
	};
}
#pragma once

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockRenderer.hpp"
#include "BlockRayCaster.hpp"
#include "gui/RectangleRenderer.hpp"
#include "HUD.hpp"

namespace mpp
{
	class Window;

	class World
	{
	public:
		World ( Window &, BlockTypeRegistry const & );

		void Update ();
		void Render ();
		void RenderGUI ();

		void CreateBlock ( std::string const &, glm::vec3 const & );
		void DestroyBlock ( Block * );

	private:
		void SelectBlock ( Block * );

		Camera camera;
		std::list <Block> blocks;
		BlockRenderer blockRenderer;
		BlockRayCaster blockRayCaster;
		Block * selectedBlock { nullptr };
		Directions selectedBlockFaceDirection;
		RectangleRenderer rectangleRenderer;
		HUD hud;
	};
}
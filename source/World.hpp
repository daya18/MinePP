#pragma once

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockRenderer.hpp"
#include "BlockRayCaster.hpp"
#include "gui/RectangleRenderer.hpp"
#include "InventoryHUD.hpp"
#include "gui/BlockThumbnailRenderer.hpp"
#include "BlockCache.hpp"
#include "Inventory.hpp"

namespace mpp
{
	class Window;

	class World
	{
	public:
		World ( Window & );

		void Update ();
		void Render ();
		void RenderGUI ();

		void CreateBlock ( std::string const &, glm::vec3 const & );
		void DestroyBlock ( Block * );

	private:
		void SelectBlock ( Block * );

		Camera camera;
		BlockCache blockCache;
		BlockRayCaster blockRayCaster;
		BlockRenderer blockRenderer;
		std::list <Block> blocks;
		BlockThumbnailRenderer blockThumbnailRenderer;
		Block * selectedBlock { nullptr };
		Directions selectedBlockFaceDirection;
		RectangleRenderer rectangleRenderer;
		Inventory playerInventory;
		InventoryHUD inventoryHud;
	};
}
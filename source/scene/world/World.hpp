#pragma once

#include "Camera.hpp"
#include "Block.hpp"
#include "BlockRenderer.hpp"
#include "BlockRayCaster.hpp"
#include "../../gui/RectangleRenderer.hpp"
#include "InventoryHUD.hpp"
#include "../../gui/BlockThumbnailRenderer.hpp"
#include "BlockCache.hpp"
#include "Inventory.hpp"
#include "../Scene.hpp"
#include "../../gui/TextRenderer.hpp"

namespace mpp
{
	class Application;

	class World : public Scene
	{
	public:
		World ( Application & );

		void Render () override;
		void RenderImGui () override;
		void Update ( float delta ) override;

		bool CheckPaused () const;
		
		Application & GetApplication ();
		BlockCache & GetBlockCache ();
		RectangleRenderer & GetRectangleRenderer ();
		TextRenderer & GetTextRenderer ();

	private:
		void CreateBlock ( std::string const &, glm::vec3 const & );
		void DestroyBlock ( Block * );
		void SelectBlock ( Block * );
		void SetPaused ( bool );
		void OnKeyAction ( int key, int action );
		void OnButtonAction ( int button, int action );
		void RenderCrosshair ();

		Application * application;
		Window * window;
		Camera camera;
		BlockCache blockCache;
		BlockRayCaster blockRayCaster;
		BlockRenderer blockRenderer;
		std::list <Block> blocks;
		BlockThumbnailRenderer blockThumbnailRenderer;
		Block * selectedBlock { nullptr };
		Directions selectedBlockFaceDirection;
		RectangleRenderer rectangleRenderer;
		TextRenderer textRenderer;
		Inventory playerInventory;
		InventoryHUD inventoryHud;
		bool paused { false };
	};



	// Implementation
	inline bool World::CheckPaused () const { return paused; }
	inline Application & World::GetApplication () { return *application; }
	inline BlockCache & World::GetBlockCache () { return blockCache; }
	inline RectangleRenderer & World::GetRectangleRenderer () { return rectangleRenderer; }
	inline TextRenderer & World::GetTextRenderer () { return textRenderer; }
}

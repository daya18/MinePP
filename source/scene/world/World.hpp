#pragma once

#include "Camera.hpp"
#include "Block.hpp"
#include "WorldCache.hpp"
#include "../../gui/RectangleRenderer.hpp"
#include "InventoryHUD.hpp"
#include "../../gui/BlockThumbnailRenderer.hpp"
#include "BlockCache.hpp"
#include "Inventory.hpp"
#include "../Scene.hpp"
#include "../../gui/TextRenderer.hpp"
#include "Chunk.hpp"

namespace mpp
{
	class Application;

	class World : public Scene
	{
	public:
		World ( Application & );
		World ( World const & ) = delete;
		World ( World && ) = delete;

		World & operator = ( World const & ) = delete;
		World & operator = ( World && ) = delete;

		void Render () override;
		void RenderImGui () override;
		void Update ( float delta ) override;

		bool CheckPaused () const;
		
		Application & GetApplication ();
		BlockCache & GetBlockCache ();
		RectangleRenderer & GetRectangleRenderer ();
		TextRenderer & GetTextRenderer ();
		WorldCache & GetCache ();

	private:
		void SelectBlock ( Block * );
		void SetPaused ( bool );
		void OnKeyAction ( int key, int action );
		void OnButtonAction ( int button, int action );
		void RenderCrosshair ();
		void HandleSelection ();
		bool CheckRayIntersectionWithBlock ( Ray const &, Block const * & block, Directions & faceDirection, float & distance );

		Application * application;
		Window * window;
		Camera camera;
		BlockCache blockCache;
		WorldCache cache;
		std::list <Chunk> chunks;
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
	inline WorldCache & World::GetCache () { return cache; }
}

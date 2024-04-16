#pragma once

#include <vector>

#include "../../gui/Rectangle.hpp"

namespace mpp
{
	class BlockCache;
	class RectangleRenderer;
	class Window;
	class Inventory;

	class InventoryHUD
	{
	public:
		InventoryHUD ( BlockCache &, RectangleRenderer &, Window &, Inventory const & );

		void Update ();
		void SelectItemSlot ( int index );
		int GetSelectedItemSlot () const;

	private:
		float itemSlotSize { 70.0f };
		int itemSlotCount { 6 };
		float itemSlotMargin { 6.0f };
		float inventoryHUDBottomMargin { 10.0f };
		float itemStackMargin { 5.0f };
		glm::vec4 itemSlotInactiveColor { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 itemSlotActiveColor { 0.0f, 1.0f, 0.0f, 1.0f };

		void Initialize ();

		BlockCache * blockCache;
		RectangleRenderer * rectangleRenderer;
		Window * window;
		Inventory const * inventory;

		Rectangle background;
		std::vector <Rectangle> itemSlots;
		std::vector <Rectangle> itemStacks;
		int selectedSlot { 0 };
	};



	// Implementation
	inline int InventoryHUD::GetSelectedItemSlot () const { return selectedSlot; }
}
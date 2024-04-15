#pragma once

#include <vector>

#include "gui/Rectangle.hpp"

namespace mpp
{
	class BlockCache;
	class RectangleRenderer;

	class InventoryHUD
	{
	public:
		InventoryHUD ( BlockCache &, RectangleRenderer & );

		void SetItemSlotContents ( int slotIndex, std::string const & itemType, int itemCount );
		void SelectItemSlot ( int index );

	private:
		float itemSlotSize { 70.0f };
		int itemSlotCount { 6 };
		float itemSlotMargin { 6.0f };
		float inventoryHUDBottomMargin { 10.0f };
		float itemStackMargin { 5.0f };
		glm::vec4 itemSlotInactiveColor { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 itemSlotActiveColor { 1.0f, 1.0f, 0.0f, 1.0f };

		void Initialize ();

		BlockCache * blockCache;
		RectangleRenderer * rectangleRenderer;
		Rectangle background;
		std::vector <Rectangle> itemSlots;
		std::vector <Rectangle> itemStacks;
	};
}
#pragma once

#include "../../gui/Rectangle.hpp"
#include "../../gui/Text.hpp"

namespace mpp
{
	class World;
	class BlockCache;
	class RectangleRenderer;
	class Window;
	class Inventory;

	class InventoryHUD
	{
	public:
		InventoryHUD ( World &, Inventory const & );

		void Update ();
		void SelectItemSlot ( int index );
		int GetSelectedItemSlot () const;

	private:
		struct ItemSlotGUI
		{
			Rectangle itemSlot;
			Rectangle itemStack;
			Text itemCount;
		};

		float itemSlotSize { 70.0f };
		int itemSlotCount { 6 };
		float itemSlotMargin { 6.0f };
		float inventoryHUDBottomMargin { 10.0f };
		float itemStackMargin { 5.0f };
		glm::vec4 itemSlotInactiveColor { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 itemSlotActiveColor { 0.0f, 1.0f, 0.0f, 1.0f };

		void Initialize ();

		World * world;
		BlockCache * blockCache;
		RectangleRenderer * rectangleRenderer;
		Window * window;
		Inventory const * inventory;

		Rectangle background;
		std::vector <ItemSlotGUI> itemSlots;
		int selectedSlot { 0 };
	};



	// Implementation
	inline int InventoryHUD::GetSelectedItemSlot () const { return selectedSlot; }
}
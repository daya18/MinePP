#include "InventoryHUD.hpp"

#include "gui/RectangleRenderer.hpp"
#include "Window.hpp"
#include "BlockCache.hpp"

#include <iostream>

namespace mpp
{
	InventoryHUD::InventoryHUD ( BlockCache & blockCache, RectangleRenderer & rectangleRenderer )
	: 
		blockCache ( & blockCache ),
		rectangleRenderer ( &rectangleRenderer )
	{
		Initialize ();
	}
	
	void InventoryHUD::Initialize ()
	{
		background.SetColor ( { 0.0f, 0.0f, 0.0f, 1.0f } );

		background.GetTransform ().SetScale ( {
			itemSlotCount * ( itemSlotSize + itemSlotMargin ) + itemSlotMargin,
			itemSlotSize + itemSlotMargin * 2.0f,
			1.0f
			} );

		background.GetTransform ().SetPosition ( {
			( rectangleRenderer->GetWindow ().GetSize ().x - background.GetTransform ().GetScale ().x ) * 0.5f,
			rectangleRenderer->GetWindow ().GetSize ().y - background.GetTransform ().GetScale ().y - inventoryHUDBottomMargin,
			0.0f
			} );

		rectangleRenderer->AddRectangle ( background );

		auto slotPosition { background.GetTransform ().GetPosition () };
		slotPosition += itemSlotMargin;

		for ( int i { 0 }; i < itemSlotCount; ++i )
		{
			itemSlots.push_back ( {} );
			itemSlots.back ().GetTransform ().SetScale ( { itemSlotSize, itemSlotSize, 1.0f } );
			itemSlots.back ().GetTransform ().SetPosition ( slotPosition );
			itemSlots.back ().SetColor ( { 1.0f, 1.0f, 1.0f, 1.0f } );

			itemStacks.push_back ( {} );
			itemStacks.back ().GetTransform ().SetScale ( { itemSlotSize - itemStackMargin * 2.0f, itemSlotSize - itemStackMargin * 2.0f, 1.0f } );
			itemStacks.back ().GetTransform ().SetPosition ( slotPosition + itemStackMargin );
			itemStacks.back ().SetColor ( { 1.0f, 1.0f, 1.0f, 1.0f } );

			slotPosition.x += itemSlotSize + itemSlotMargin;
		}

		for ( auto const & itemSlot : itemSlots )
			rectangleRenderer->AddRectangle ( itemSlot );

		for ( auto const & itemStack : itemStacks )
			rectangleRenderer->AddRectangle ( itemStack );
	}
	
	void InventoryHUD::SetItemSlotContents ( int slotIndex, std::string const & itemType, int itemCount )
	{
		itemStacks [ slotIndex ].SetTexture ( blockCache->GetBlockThumbnailTexture ( itemType ) );
	}

	void InventoryHUD::SelectItemSlot ( int targetIndex )
	{
		if ( targetIndex < 0 || targetIndex > itemSlots.size () - 1 )
			return;

		for ( int index { 0 }; index < itemSlots.size (); ++index )
		{
			if ( index == targetIndex )
			{
				itemSlots [ index ].SetColor ( itemSlotActiveColor );
				continue;
			}

			itemSlots [ index ].SetColor ( itemSlotInactiveColor );
		}
	}
}
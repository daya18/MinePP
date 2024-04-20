#include "InventoryHUD.hpp"

#include "../../gui/RectangleRenderer.hpp"
#include "../../Window.hpp"
#include "BlockCache.hpp"
#include "Inventory.hpp"
#include "World.hpp"
#include "../../Application.hpp"

namespace mpp
{
	InventoryHUD::InventoryHUD ( World & world, Inventory const & inventory )
	: 
		world ( & world ),
		inventory ( & inventory ),
		blockCache ( & world.GetBlockCache () ),
		window ( & world.GetApplication ().GetWindow () ),
		rectangleRenderer ( & world.GetRectangleRenderer () )
	{
		Initialize ();

		SelectItemSlot ( 0 );

		window->AddScrollCallback ( [ this ] ( glm::vec2 offset ) {
			if ( offset.y > 0.0f )
				SelectItemSlot ( selectedSlot - 1 );
			else if ( offset.y < 0.0f )
				SelectItemSlot ( selectedSlot + 1 );
		} );

		Update ();
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

		glm::vec3 slotPosition { 
			background.GetTransform ().GetPosition ().x + itemSlotMargin,
			background.GetTransform ().GetPosition ().y + itemSlotMargin,
			1.0f
		};

		for ( int i { 0 }; i < itemSlotCount; ++i )
		{
			itemSlots.push_back ( {} );
			auto & slot { itemSlots.back () };

			slot.itemSlot.GetTransform ().SetScale ( { itemSlotSize, itemSlotSize, 1.0f } );
			slot.itemSlot.GetTransform ().SetPosition ( slotPosition );
			slot.itemSlot.SetColor ( { 1.0f, 1.0f, 1.0f, 1.0f } );

			slot.itemStack.GetTransform ().SetScale ( { itemSlotSize - itemStackMargin * 2.0f, itemSlotSize - itemStackMargin * 2.0f, 1.0f } );
			slot.itemStack.GetTransform ().SetPosition ( { slotPosition.x + itemStackMargin, slotPosition.y + itemStackMargin, 2.0f } );
			slot.itemStack.SetColor ( { 1.0f, 1.0f, 1.0f, 1.0f } );

			auto countPosition { slot.itemStack.GetTransform ().GetPosition () };
			countPosition += slot.itemStack.GetTransform ().GetScale ();
			slot.itemCount.origin = { 1.0f, 1.0f };
			slot.itemCount.color = { 0.0f, 0.0f, 0.0f, 1.0f };
			slot.itemCount.transform.SetPosition ( { countPosition.x, countPosition.y, 3.0f } );
			slot.itemCount.transform.SetScale ( { 0.5f, 0.5f, 1.0f } );

			slotPosition.x += itemSlotSize + itemSlotMargin;
		}

		for ( auto const & itemSlot : itemSlots )
		{
			rectangleRenderer->AddRectangle ( itemSlot.itemSlot );
			rectangleRenderer->AddRectangle ( itemSlot.itemStack );
			world->GetTextRenderer ().AddText ( itemSlot.itemCount );
		}
	}
	
	void InventoryHUD::Update ()
	{
		int index { 0 };
		for ( auto & itemSlot : itemSlots )
		{
			auto & const slot { inventory->GetSlot ( index ) };

			if ( slot.HasStack () )
			{
				itemSlot.itemStack.SetTexture ( &blockCache->GetBlockThumbnailTexture ( slot.GetStack().GetItemType () ) );
				itemSlot.itemCount.text = std::to_string ( slot.GetStack ().GetItemCount () );
			}
			else
			{
				itemSlot.itemStack.SetTexture ( nullptr );
				itemSlot.itemCount.text.clear ();
			}

			++index;

			//world->GetTextRenderer ().RemoveText ( itemSlot.itemCount );
			//world->GetTextRenderer ().AddText ( itemSlot.itemCount );
		}
	}

	void InventoryHUD::SelectItemSlot ( int targetIndex )
	{
		if ( targetIndex < 0 || targetIndex > itemSlots.size () - 1 )
			return;

		selectedSlot = targetIndex;

		for ( int index { 0 }; index < itemSlots.size (); ++index )
		{
			if ( index == targetIndex )
			{
				itemSlots [ index ].itemSlot.SetColor ( itemSlotActiveColor );
				continue;
			}

			itemSlots [ index ].itemSlot.SetColor ( itemSlotInactiveColor );
		}
	}
}
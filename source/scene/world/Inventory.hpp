#pragma once

namespace mpp
{
	class ItemStack
	{
	public:
		ItemStack ();
		ItemStack ( std::string const & type, int count );

		std::string const & GetItemType () const;
		int GetItemCount () const;

	private:
		std::string itemType { "Null" };
		int itemCount { 0 };
	};

	class ItemSlot
	{
	public:
		ItemSlot ();

		void SetStack ( ItemStack const & );
		void Clear ();
		bool HasStack () const;
		ItemStack const & GetStack () const;

	private:
		bool hasStack { false };
		ItemStack stack;
	};

	class Inventory
	{
	public:
		Inventory ( int slotCount );

		std::vector <ItemSlot> const & GetSlots () const;
		ItemSlot const & GetSlot ( int index ) const;
		ItemSlot & GetSlot ( int index );

	private:
		std::vector <ItemSlot> itemSlots;
	};



	// Implementation
	inline ItemStack::ItemStack () {}
	inline ItemStack::ItemStack ( std::string const & type, int count )
		: itemType ( type ), itemCount ( count ) {}

	inline std::string const & ItemStack::GetItemType () const { return itemType; }
	inline int ItemStack::GetItemCount () const { return itemCount; }

	inline ItemSlot::ItemSlot () {}
	inline void ItemSlot::SetStack ( ItemStack const & stack ) { this->stack = stack; hasStack = true; }
	inline void ItemSlot::Clear () { hasStack = false; }
	inline bool ItemSlot::HasStack () const { return hasStack; }
	inline ItemStack const & ItemSlot::GetStack () const { return stack; }

	inline Inventory::Inventory ( int slotCount ) : itemSlots ( slotCount ) {}
	inline std::vector <ItemSlot> const & Inventory::GetSlots () const { return itemSlots; }
	inline ItemSlot const & Inventory::GetSlot ( int index ) const { return itemSlots [ index ]; }
	inline ItemSlot & Inventory::GetSlot ( int index ) { return itemSlots [ index ]; }
}
#pragma once

namespace mpp
{
	class BlockType
	{
		std::string texturePath;
	};

	class BlockTypeRegistry
	{
	public:

	private:
		std::unordered_map <std::string, BlockType> namedBlockTypes;
	};
}
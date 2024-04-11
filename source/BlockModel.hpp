#pragma once

#include <array>

#include "Constants.hpp"

namespace mpp
{
	class BlockModel
	{
	public:
		BlockModel ();

		std::vector <float> const & GetRawVertices () const;
		std::vector <uint32_t> const & GetRawIndices () const;
		uint32_t GetFaceIndexOffset ( Directions ) const;

	private:
		std::vector <float> vertices;
		std::vector <uint32_t> indices;
		std::unordered_map <Directions, uint32_t> faceIndexOffsets;
	};



	inline std::vector <float> const & BlockModel::GetRawVertices () const { return vertices; }
	inline std::vector <uint32_t> const & BlockModel::GetRawIndices () const { return indices; }
	inline uint32_t BlockModel::GetFaceIndexOffset ( Directions direction ) const { return faceIndexOffsets.at (direction); }
}
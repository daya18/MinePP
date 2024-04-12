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
		uint32_t GetFaceRawIndexOffset ( Directions ) const;

		std::array <glm::vec3, 8> const & GetVertices () const;
		std::array <uint32_t, 6> const & GetFaceIndices ( Directions ) const;

	private:
		std::vector <float> rawVertices;
		std::vector <uint32_t> rawIndices;
		std::unordered_map <Directions, uint32_t> faceRawIndexOffsets;
		
		std::array <glm::vec3, 8> vertices;
		std::unordered_map <Directions, std::array <uint32_t, 6>> faceIndices;
	};



	inline std::vector <float> const & BlockModel::GetRawVertices () const { return rawVertices; }
	inline std::vector <uint32_t> const & BlockModel::GetRawIndices () const { return rawIndices; }
	inline uint32_t BlockModel::GetFaceRawIndexOffset ( Directions direction ) const { return faceRawIndexOffsets.at (direction); }
	
	inline std::array <glm::vec3, 8> const & BlockModel::GetVertices () const { return vertices; }
	
	inline std::array <uint32_t, 6> const & BlockModel::GetFaceIndices ( Directions direction ) const 
	{ return faceIndices.at ( direction ); }
}
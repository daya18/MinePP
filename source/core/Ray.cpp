#include "Ray.hpp"

#include "Constants.hpp"

namespace mpp
{
	bool CheckRayIntersectBox ( Ray const & ray, Box const & box, glm::vec3 & normal, float & distance )
	{
		glm::vec3 boxHalfSize { box.size * 0.5f };

		std::array <glm::vec3, 8> const boxVertices
		{
			// Front plane ( Z+ )
			box.center + glm::vec3 { -boxHalfSize.x, -boxHalfSize.y,  boxHalfSize.z }, // 0
			box.center + glm::vec3 { -boxHalfSize.x,  boxHalfSize.y,  boxHalfSize.z }, // 1
			box.center + glm::vec3 {  boxHalfSize.x,  boxHalfSize.y,  boxHalfSize.z }, // 2
			box.center + glm::vec3 {  boxHalfSize.x, -boxHalfSize.y,  boxHalfSize.z }, // 3
			
			// Back plane ( Z- )
			box.center + glm::vec3 { -boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z }, // 4
			box.center + glm::vec3 { -boxHalfSize.x,  boxHalfSize.y, -boxHalfSize.z }, // 5
			box.center + glm::vec3 {  boxHalfSize.x,  boxHalfSize.y, -boxHalfSize.z }, // 6
			box.center + glm::vec3 {  boxHalfSize.x, -boxHalfSize.y, -boxHalfSize.z }, // 7
		};

		static std::unordered_map <glm::vec3, std::array < std::array <uint32_t, 3>, 2 > > const boxFaceIndices
		{
			// Face Normal							// Face indices per triangle
			{ glm::vec3 {  0.0f,  0.0f,  1.0f },	{ std::array <uint32_t, 3> { 0, 1, 2 }, std::array <uint32_t, 3> { 2, 3, 0 } } },
			{ glm::vec3 {  0.0f,  0.0f, -1.0f },	{ std::array <uint32_t, 3> { 4, 5, 6 }, std::array <uint32_t, 3> { 6, 7, 4 } } },
			{ glm::vec3 { -1.0f,  0.0f,  0.0f },	{ std::array <uint32_t, 3> { 0, 1, 5 }, std::array <uint32_t, 3> { 5, 4, 0 } } },
			{ glm::vec3 {  1.0f,  0.0f,  0.0f },	{ std::array <uint32_t, 3> { 6, 7, 3 }, std::array <uint32_t, 3> { 3, 2, 6 } } },
			{ glm::vec3 {  0.0f,  1.0f,  0.0f },	{ std::array <uint32_t, 3> { 1, 5, 6 }, std::array <uint32_t, 3> { 6, 2, 1 } } },
			{ glm::vec3 {  0.0f, -1.0f,  0.0f },	{ std::array <uint32_t, 3> { 4, 0, 3 }, std::array <uint32_t, 3> { 3, 7, 4 } } },
		};

		struct FaceIntersection
		{
			glm::vec3 normal;
			float distance;
		};

		std::vector <FaceIntersection> faceIntersections;

		for ( auto const & [faceNormal, faceTriangleIndices] : boxFaceIndices )
		{
			bool intersects { false };
			float distance { 0.0f };

			for ( auto const & triangleIndices : faceTriangleIndices )
			{
				glm::vec2 baryPosition;

				intersects = glm::intersectRayTriangle ( ray.origin, ray.direction,
					boxVertices [ triangleIndices [ 0 ] ],
					boxVertices [ triangleIndices [ 1 ] ],
					boxVertices [ triangleIndices [ 2 ] ],
					baryPosition,
					distance
				);

				if ( intersects )
					break;
			}

			if ( intersects )
				faceIntersections.push_back ( { faceNormal, distance } );
		}

		if ( ! faceIntersections.empty () )
		{
			normal = glm::zero <glm::vec3> ();
			distance = std::numeric_limits <float>::infinity ();

			for ( auto const & faceIntersection : faceIntersections )
			{
				if ( faceIntersection.distance < distance )
				{
					normal = faceIntersection.normal;
					distance = faceIntersection.distance;
				}
			}
		}

		return ! faceIntersections.empty ();
	}

	bool CheckPointInBox ( glm::vec3 const & point, Box const & box )
	{
		glm::vec3 boxHalfSize { box.size * 0.5f };
		auto boxMin { box.center - boxHalfSize };
		auto boxMax { box.center + boxHalfSize };

		if ( point.x < boxMin.x || point.x > boxMax.x )
			return false;

		//std::cout << 1 << std::endl;
		
		if ( point.y < boxMin.y || point.y > boxMax.y )
			return false;
		
		//std::cout << 2 << std::endl;

		if ( point.z < boxMin.z || point.z > boxMax.z )
			return false;
		
		//std::cout << 3 << std::endl;

		return true;
	}
}
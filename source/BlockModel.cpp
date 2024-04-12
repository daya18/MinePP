#include "BlockModel.hpp"

#include <OBJ_Loader.h>

namespace mpp
{
	BlockModel::BlockModel ()
	{
		static const std::unordered_map <std::string, Directions> meshNameFaceDirections
		{
			{ "FrontFace", Directions::forward },
			{ "BackFace",  Directions::back },
			{ "LeftFace", Directions::left },
			{ "RightFace", Directions::right },
			{ "TopFace", Directions::up },
			{ "BottomFace", Directions::down },
		};

		objl::Loader loader;
		loader.LoadFile ( "model/Block.obj" );

		for ( auto const & vertex : loader.LoadedVertices )
		{
			rawVertices.push_back ( vertex.Position.X );
			rawVertices.push_back ( vertex.Position.Y );
			rawVertices.push_back ( vertex.Position.Z );

			rawVertices.push_back ( vertex.TextureCoordinate.X );
			rawVertices.push_back ( vertex.TextureCoordinate.Y );
		}

		for ( auto const & index : loader.LoadedIndices )
			rawIndices.push_back ( index );

		for ( auto const & faceMesh : loader.LoadedMeshes )
		{
			auto meshFaceDirectionIt { meshNameFaceDirections.find ( faceMesh.MeshName ) };

			if ( meshFaceDirectionIt == meshNameFaceDirections.end () )
				throw std::runtime_error { "Face mesh name '" + faceMesh.MeshName + "' invalid" };

			auto faceDirection { meshFaceDirectionIt->second };
		}
	}
}
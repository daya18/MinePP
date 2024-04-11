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
			vertices.push_back ( vertex.Position.X );
			vertices.push_back ( vertex.Position.Y );
			vertices.push_back ( vertex.Position.Z );

			vertices.push_back ( vertex.TextureCoordinate.X );
			vertices.push_back ( vertex.TextureCoordinate.Y );
		}

		for ( auto const & index : loader.LoadedIndices )
			indices.push_back ( index );

		for ( auto const & mesh : loader.LoadedMeshes )
		{
			auto meshFaceDirectionIt { meshNameFaceDirections.find ( mesh.MeshName ) };
		}
	}
}
#include "Scene.hpp"

#include <OBJ_Loader.h>

namespace mpp
{
	Scene::Scene ( std::string const & filePath )
	{
		objl::Loader loader;
		loader.LoadFile ( filePath );

		for ( auto const & mesh : loader.LoadedMeshes )
		{
			meshes.push_back ( {} );
			
			meshes.back ().name = mesh.MeshName;

			for ( auto const & vertex : mesh.Vertices )
			{
				meshes.back().vertices.push_back ( {
					{ vertex.Position.X, vertex.Position.Y, vertex.Position.Z },
					{ vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y },
					{ vertex.Normal.X,vertex.Normal.Y, vertex.Normal.Z }
				} );
			}

			for ( auto const & index : mesh.Indices )
				meshes.back ().indices.push_back ( index );
		}
	}
}
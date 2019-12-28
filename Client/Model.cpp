#include "Model.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "DirectXMath.h"
#include <vector>
#include <sstream>
#include <fstream>

Model::Model( const std::string& name, const Material& m ) {
	std::ifstream ifs( "Resources\\" + name + ".obj");
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

	std::string line;
	std::stringstream ss;

	while ( std::getline( ifs, line ) ) {
		ss = std::stringstream( line );
		if ( line.length() < 2 ) continue;

		if ( line[0] == 'v' && line[1] == ' ' ) {	// line specifies a vertex
			
			std::string lineType;	// something to store the v and space in
			float x, y, z;			// the three 

			ss >> lineType >> x >> y >> z;
			
			vertices.push_back( { x, y, z } );
		}

		if ( line[0] == 'f' && line[1] == ' ' ) {	// line specifies a face

			std::string garbage;		// a place to put all the junk
			unsigned short i1, i2, i3;	// the three indices of the triangle

			ss >> garbage >> i1 >> garbage >> i2 >> garbage >> i3;
			
			indices.push_back( i1 - 1 );	// subtract 1 because obj indices starts at 1
			indices.push_back( i2 - 1 );
			indices.push_back( i3 - 1 );
		}

	}

	AddBindable( std::make_shared<VertexBuffer>( &vertices[0], vertices.size() ) );

	AddBindable( std::make_shared<IndexBuffer>( &indices[0], indices.size() ) );

	using namespace DirectX;
	pTransformBuffer = std::make_shared< ConstantBuffer<XMMATRIX, VS, 0u>>( &XMMatrixIdentity() );
	AddBindable( pTransformBuffer );

	pMaterialBuffer = std::make_shared < ConstantBuffer < Material, PS, 0u > >( &m );
	AddBindable( pMaterialBuffer );
}

void Model::Draw( const DirectX::XMMATRIX& transform ) {
	pTransformBuffer->Set( &DirectX::XMMatrixTranspose( transform ) );
	Drawable::Draw();
}

void Model::SetMaterial( const Material& mtl ) {
}

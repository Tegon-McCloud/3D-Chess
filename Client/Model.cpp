#include "Model.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DirectXMath.h"

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
			
			std::string lineType;
			float x, y, z;

			ss >> lineType >> x >> y >> z;
			
			vertices.push_back( { x, y, z } );
		}

		if ( line[0] == 'f' && line[1] == ' ' ) {

			std::string garbage;
			unsigned short triangle[3];

			ss >> garbage >> triangle[0] >> garbage >> triangle[1] >> garbage >> triangle[2];
			
			indices.push_back( triangle[0] - 1 );
			indices.push_back( triangle[1] - 1 );
			indices.push_back( triangle[2] - 1 );
		}

	}

	AddBindable( std::make_shared<VertexBuffer>( &vertices[0], vertices.size() ) );

	AddBindable( std::make_shared<IndexBuffer>( &indices[0], indices.size() ) );

	using namespace DirectX;
	auto cb = std::make_shared< ConstantBuffer < XMMATRIX, VS, 0u > >( &XMMatrixIdentity() );
	pTransformBuffer = cb;
	AddBindable( std::move( cb ) );

	AddBindable( std::make_shared < ConstantBuffer < Material, PS, 0u > >( &m ) );
}

void Model::Draw( const DirectX::XMMATRIX& transform ) {
	pTransformBuffer->Set( &DirectX::XMMatrixTranspose( transform ) );
	Drawable::Draw();
}

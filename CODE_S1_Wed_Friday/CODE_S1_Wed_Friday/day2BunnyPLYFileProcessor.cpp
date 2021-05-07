// day2BunnyPLYFileProcessor

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//sVertex_XYZ_RGB vertices[3] =
//{
//    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
//    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
//    {   0.f,  0.6f, 0.f, 0.f, 1.f }
//};

bool readToToken(std::ifstream &theFile, std::string theToken)
{
	std::string currentToken;
	while ( theFile >> currentToken )
	{
		if ( currentToken == theToken )
		{
			return true;
		}
	}
	// Didn't find it
	return false;
}

bool generateQnDHeaderFileFromPLY( std::string plyFileName, 
								   std::string headerFileName, 
								   unsigned int &numVertices )
{
	std::ifstream plyFile(plyFileName.c_str());
	if ( ! plyFile.is_open() )
	{
		return false;
	}

	readToToken(plyFile, "vertex");

	unsigned int numVerticesInFile = 0;
	plyFile >> numVerticesInFile;


	readToToken(plyFile, "face");

	unsigned int numFaces = 0;
	plyFile >> numFaces;

	readToToken(plyFile, "end_header");

	struct sVertex
	{
		float x, y, z;
	};
	struct sFace
	{
		unsigned int v0, v1, v2;
	};

	std::vector< sVertex > vecVertices;
	std::vector< sFace > vecFaces;

	std::cout << "Reading " << numVerticesInFile << " vertices...";
	for ( unsigned int count = 0; count != numVerticesInFile; count++ )
	{
		//-0.0369122 0.127512 0.00276757 0.850855 0.5 
		sVertex curVertex;
		plyFile >> curVertex.x >> curVertex.y >> curVertex.z;
		vecVertices.push_back(curVertex);

		float ignore = 0.0f;
		plyFile >> ignore >> ignore;
	}
	std::cout << "done." << std::endl;

	std::cout << "Reading " << numFaces << " triangles...";
	for (unsigned int count = 0; count != numFaces; count++ )
	{
		//3 562 520 580 
		sFace curFace;
		int ignore = 0;
		plyFile >> ignore >> curFace.v0 >> curFace.v1 >> curFace.v2;
		vecFaces.push_back(curFace);
	}
	std::cout << "done." << std::endl;

	plyFile.close();

	std::cout << "Generating flat vertex list...";
	std::vector< sVertex > vecFlatVertices;
	for ( unsigned int index = 0; index != numFaces; index++ )
	{
		vecFlatVertices.push_back( vecVertices[ vecFaces[index].v0 ] );
		vecFlatVertices.push_back( vecVertices[ vecFaces[index].v1 ] );
		vecFlatVertices.push_back( vecVertices[ vecFaces[index].v2 ] );
	}
	std::cout << "done." << std::endl;

	//sVertex_XYZ_RGB vertices[3] =
	//{
	//    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
	//    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
	//    {   0.f,  0.6f, 0.f, 0.f, 1.f }
	//};

	std::cout << "Generating header file of " << vecFlatVertices.size() << "...";

	std::ofstream headerFile(headerFileName.c_str());
	headerFile << "{" << std::endl;

	for ( unsigned int index = 0; index != vecFlatVertices.size(); index++ )
	{
		headerFile 
			<< "\t{ " 
			<< vecFlatVertices[index].x << "f, "
			<< vecFlatVertices[index].y << "f, "
//			<< vecFlatVertices[index].z << "f, "
			<< "1.0f, "	// Red
			<< "1.0f, " // Green
			<< "1.0f " // Blue
			<< "}";
		
		// Last line?
		if ( index != (vecFlatVertices.size() - 1) )
		{
			// Nope
			headerFile << ",";
		}
		headerFile << std::endl;
	}//for ( unsigned int index = 0

	headerFile << "};" << std::endl;
	headerFile << std::endl;

	headerFile << "const unsigned int NUM_VERTICES = " << vecFlatVertices.size() << ";" << std::endl;
	headerFile << std::endl;


	std::cout << "done." << std::endl;

	headerFile.close();

	return true;
}

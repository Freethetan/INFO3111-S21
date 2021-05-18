#include "cMeshObject.h"

cMeshObject::cMeshObject()
{
	this->meshName = "";
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);

	this->wholeObjectColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);	// 0,0,0,1 (black)

	this->orientation = glm::vec3(0.0f, 0.0f, 0.0f);		// Euler angles (x, y, and z)
	
	this->scale = 1.0f; // 1.0f

	this->isWireframe = false;		// false


	this->wholeObjectColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// bright white
	this->bUseVertexColours = true;         // If true, then use the file colours

}
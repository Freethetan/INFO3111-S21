#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

class cMeshObject
{
public:
    cMeshObject()
    {
        this->meshName = "";
        this->position = glm::vec3(0.0f,0.0f,0.0f);
        this->orientation = glm::vec3(0.0f,0.0f,0.0f);
        this->wholeObjectColour = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        this->scale = 1.0f; 
        this->isWireframe = false;
    }
    ~cMeshObject() {};
    std::string meshName;
    glm::vec3 position;		// 0,0,0 (origin)
    glm::vec4 wholeObjectColour;	// 1,1,1,1 (white)
    glm::vec3 orientation;		// Euler angles (x, y, and z)
    float scale;			// 1.0f
    bool isWireframe;		// false
};

#endif // _cMeshObject_HG_

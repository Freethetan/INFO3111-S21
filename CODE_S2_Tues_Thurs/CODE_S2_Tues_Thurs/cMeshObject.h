#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include "globalStuff.h"    

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

class cMeshObject
{
public:
    cMeshObject();
    ~cMeshObject() {};
    std::string meshName;
    glm::vec3 position;		// 0,0,0 (origin)
    glm::vec4 wholeObjectColour;	// 0,0,0,1 (black)
    glm::vec3 orientation;		// Euler angles (x, y, and z)
    float scale;			// 1.0f
    bool isWireframe;		// false

    // We can set this to set the entire model to one colour
    bool bUseVertexColours;         // If true, then use the file colours
};

#endif // _cMeshObject_HG_

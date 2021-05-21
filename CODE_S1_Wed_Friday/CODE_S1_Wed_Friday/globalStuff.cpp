#include "globalStuff.h"



glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, -4.0f);
glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);



eProgramMode g_CurrentMode = CAMERA_VIEW;

// Anything that's in this vector is drawn to the screen
// (so this is basically the "scene" we want to draw)
std::vector<cMeshObject> g_vecObjectsToDraw;

// This is the "selected" object
std::vector<cMeshObject>::iterator itSelectedObject = g_vecObjectsToDraw.begin();

cMeshObject g_DebugCube;
cMeshObject g_DebugSphere;
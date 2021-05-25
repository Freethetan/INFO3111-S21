//globalStuff.cpp

#include "globalStuff.h"

#include "cMeshObject.h"

// This is the ONE AND ONLY ONE PLACE that these are
glm::vec3 g_CameraEye = glm::vec3(0.0, 0.0, -4.0f);
glm::vec3 g_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

// This will be read and displayed each frame
std::string g_CurrentWindowTitle = "I got my COVID shot";

eKeyboardMode g_KeyboardMode = CAMERA;

// This is the index of the model I'm currently "editing"
unsigned int g_EditModelIndex = 0;

std::vector<cMeshObject> g_vecMyModels;

cMeshObject g_Debug1x1x1Cube;
cMeshObject g_DebugSphere;

sLight g_Light0;
cLightManager* g_pLightManager = NULL;
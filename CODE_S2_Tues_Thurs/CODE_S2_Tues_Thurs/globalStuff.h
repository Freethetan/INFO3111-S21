#pragma once

// globalStuff.h

// This is here because glad has to be included 
// BEFORE glfw or it won't build.
// Since we can't control the order of the build
// (which cpp file is compiled 1st, etc.), they
// all include this, ensuring it's A-OK
// 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

//#include "cMeshObject.h"
class cMeshObject;		// Forward declare

#include <string>
#include <vector>

extern glm::vec3 g_CameraEye;
extern glm::vec3 g_CameraTarget;

// This will be read and displayed each frame
extern std::string g_CurrentWindowTitle;

// GFLW sync keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// We call this every frame
void asyncKeyboardMouse(GLFWwindow* pWindow);

enum eKeyboardMode
{
	CAMERA, 
	EDIT
};

extern eKeyboardMode g_KeyboardMode;

// This is the index of the model I'm currently "editing"
extern unsigned int g_EditModelIndex;

extern std::vector<cMeshObject> g_vecMyModels;


extern cMeshObject g_Debug1x1x1Cube;
extern cMeshObject g_DebugSphere;
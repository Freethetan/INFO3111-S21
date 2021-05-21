#pragma once
// globalStuff.h

// This to make sure these are "found" in the correct order
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <vector>
#include <string>

#include "cMeshObject.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void doKeyboardMouseStuffAsync(GLFWwindow* window);


extern glm::vec3 g_cameraEye;
extern glm::vec3 g_cameraTarget;

enum eProgramMode
{
	CAMERA_VIEW, 
	EDIT_VIEW,
	LIGHT_EDIT_VIEW
};

extern eProgramMode g_CurrentMode;

// Anything that's in this vector is drawn to the screen
// (so this is basically the "scene" we want to draw)
extern std::vector<cMeshObject> g_vecObjectsToDraw;

// This is the "selected" object
extern std::vector<cMeshObject>::iterator itSelectedObject;

extern cMeshObject g_DebugCube;
extern cMeshObject g_DebugSphere;
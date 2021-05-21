#pragma once
// globalStuff.h

// This to make sure these are "found" in the correct order
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void doKeyboardMouseStuffAsync(GLFWwindow* window);


extern glm::vec3 g_cameraEye;
extern glm::vec3 g_cameraTarget;


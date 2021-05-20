#include "globalStuff.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << (char)key << std::endl;
    //if (key == '1')
    //{
    //    std::cout << "Switch to wireframe." << std::endl;
    //    ::g_DrawWireframe = true;
    //}
    //if (key == '2')
    //{
    //    std::cout << "Switch to fill rendering." << std::endl;
    //    ::g_DrawWireframe = false;
    //}


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void asyncKeyboardMouse(GLFWwindow* pWindow)
{
	float cameraSpeed = 0.1f;

	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		// Move this -ve on the x axis
		::g_CameraEye.x -= cameraSpeed;
	}
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		// Move this +ve on the x axis
		::g_CameraEye.x += cameraSpeed;
	}

	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		// Move this +ve on the z axis "forward"
		::g_CameraEye.z += cameraSpeed;
	}
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		// Move this -ve on the z axis "forward"
		::g_CameraEye.z -= cameraSpeed;
	}
	// Add Q for "down" (y axis)
	// Add E for "up" (y axis)
	if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS)
	{
		// Move this -ve on the y axis "down"
		::g_CameraEye.y -= cameraSpeed;
	}
	if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS)
	{
		// Move this +ve on the y axis "up"
		::g_CameraEye.y += cameraSpeed;
	}

	return;
}

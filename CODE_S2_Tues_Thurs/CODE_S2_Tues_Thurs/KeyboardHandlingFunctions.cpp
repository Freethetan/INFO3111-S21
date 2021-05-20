#include "globalStuff.h"
#include "cMeshObject.h"

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

	// See if I should change modes
	// Alt - E = "edit", Alt - C = "camera" - default is "camera" mode)

	// This would check if ONLY the ALT modifier is down
//	if (mods == GLFW_MOD_ALT) {}
	// This would check if the Alt key is present even with other modifiers
//	if ( (mods & GLFW_MOD_ALT) == GLFW_MOD_ALT)

	if (mods == GLFW_MOD_ALT)
	{
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			::g_KeyboardMode = EDIT;
		}
		if (key == GLFW_KEY_C && action == GLFW_PRESS)
		{
			::g_KeyboardMode = CAMERA;
		}
	}//mods == GLFW_MOD_ALT



    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void asyncKeyboardMouse(GLFWwindow* pWindow)
{
	float cameraSpeed = 0.1f;

	switch (::g_KeyboardMode)
	{
	case CAMERA:
		{// STAROF: Camera mode handling
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
			if (glfwGetKey(pWindow, GLFW_KEY_E) == GLFW_PRESS)
			{
				// Move this +ve on the y axis "up"
				::g_CameraEye.y += cameraSpeed;
			}		
		}// ENDOF: Camera mode handling

		break;
	case EDIT:
		{// Edit: Camera mode handling
			cMeshObject& curObject = ::g_vecMyModels[::g_EditModelIndex];

			if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
			{
				// Move this -ve on the x axis
				curObject.position.x -= cameraSpeed;
			}
			if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
			{
				// Move this +ve on the x axis
				curObject.position.x += cameraSpeed;
			}
			// ... and son on

		}// ENDOF: Edit mode handling
		break;

	}//switch (::g_KeyboardMode)



	return;
}

// userInputHandling

#include "globalStuff.h"

void doKeyboardMouseStuffAsync(GLFWwindow* window)
{
    float cameraSpeed = 0.01f;


    switch (::g_CurrentMode)
    {
    case EDIT_VIEW:
        {//START OF: EDIT_VIEW


            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                itSelectedObject->position.x -= cameraSpeed; // Move "left"
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                itSelectedObject->position.x += cameraSpeed; // Move "right"
            }

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                itSelectedObject->position.z += cameraSpeed; // Move "forward"
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                itSelectedObject->position.z -= cameraSpeed; // Move "backward"
            }

            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                itSelectedObject->position.y -= cameraSpeed; // Move "down"
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            {
                itSelectedObject->position.y += cameraSpeed; // Move "up"
            }
        }//END OF: EDIT_VIEW
        break;
    case CAMERA_VIEW:
        {//START OF: EDIT_VIEW
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                ::g_cameraEye.x -= cameraSpeed; // Move "left"
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                ::g_cameraEye.x += cameraSpeed; // Move "right"
            }

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                ::g_cameraEye.z += cameraSpeed; // Move "forward"
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                ::g_cameraEye.z -= cameraSpeed; // Move "backward"
            }

            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                ::g_cameraEye.y -= cameraSpeed; // Move "down"
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            {
                ::g_cameraEye.y += cameraSpeed; // Move "up"
            }
        }//END OF: EDIT_VIEW
        break;
    }



    return;
}

// GLFW keyboard sync callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Change mode
    if (mods == GLFW_MOD_ALT) // Is ALT down Just By Itself
    {
        if ((key == GLFW_KEY_E) && (action == GLFW_PRESS))
        {
            ::g_CurrentMode = EDIT_VIEW;
        }
        if ((key == GLFW_KEY_C) && (action == GLFW_PRESS))
        {
            ::g_CurrentMode = CAMERA_VIEW;
        }
    }//if (mods == GLFW_MOD_ALT) 



    // You could "mask" this value, too
//    if ( (mods & GLFW_MOD_ALT) == GLFW_MOD_ALT ) // Is the Alt down (and ignore all the others)


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}















//
//if (key == '1')
//{
//    std::cout << "Switching to wireframe" << std::endl;
//    ::g_IsWireframe = true;
//}
//if (key == '2')
//{
//    std::cout << "Switching to solid fill" << std::endl;
//    ::g_IsWireframe = false;
//}
// userInputHandling

#include "globalStuff.h"

void doKeyboardMouseStuffAsync(GLFWwindow* window)
{
    float cameraSpeed = 0.01f;

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

    return;
}

// GLFW keyboard sync callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


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
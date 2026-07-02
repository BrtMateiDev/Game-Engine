#include <GLFW/glfw3.h>
#include <iostream>

int main() {
#if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

    if (!glfwInit()) return -1;

    //The window acts as an object stored in a pointer
    GLFWwindow *window = glfwCreateWindow(1280, 720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr) {
        std::cout<<"Error creating window"<<'\n';
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); //Events like the close button
    }

    glfwTerminate();

    return 0;
}
#include "GameWindow.h"

//Constructor
GameWindow::GameWindow(int width, int height)
    : m_windowHeight(height)
    , m_windowWidth(width)
    , m_window(nullptr)
{}

//Deconsturctor
GameWindow::~GameWindow() {
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    glfwTerminate();
}

//Setup function for GLFW window.
int GameWindow::SetupGLFWwindow() {

    //Initializing GLFW
    if(!glfwInit()) {
        //Error check on startup of GLFW
        std::cout << "Failed to init GLFW" << std::endl;
        glfwTerminate();
        return 1;
    }

    //Setting up hints/flags
    //Working with OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Sigils of Outri", NULL, NULL);

    //Error check on startup of m_window
    if(m_window == NULL) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return 1;
    }

    return 0;
}

int GameWindow::getWindowWidth() {
    return m_windowWidth;
}

int GameWindow::getWindowHeight() {
    return m_windowHeight;
}
//Get function returns GLFWwindow pointer
GLFWwindow * GameWindow::getWindow() {
    return m_window;
}

#include "GameEngine.h"

//settings
constexpr unsigned int WIDTH = 600;
constexpr unsigned int HEIGHT = 800;

//Function to set viewport
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

GameEngine::GameEngine(GLFWwindow * targetWindow)
    : m_window(targetWindow) {
    
    std::cout << "Initializing Engine." << std::endl;

    //Set context of the GLFWwindow
    glfwMakeContextCurrent(m_window);

    //used for user window resizing.
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    
}

GameEngine::~GameEngine() {
    std::cout << "Engine is deinitializing." << std::endl;
}

void GameEngine::processEvent(GLFWwindow *targetWindow) {
    glfwPollEvents();
    
    if(glfwGetKey(targetWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

void GameEngine::updateFPSCounter() {
    m_currentTime = glfwGetTime();
    m_frameCounter++;

    if(m_currentTime - m_previousTime >= 1.0) {
        m_frameCounter = 0;
        m_previousTime = m_currentTime;
    }
}
void GameEngine::update() {
    GameEngine::updateFPSCounter();
}

void GameEngine::draw() {
    glfwSwapBuffers(m_window);
}
void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
    std::cout << "here" << std::endl;
    glViewport(0, 0, width, height);
}
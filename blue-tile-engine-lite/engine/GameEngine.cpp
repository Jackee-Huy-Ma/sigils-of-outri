#include "GameEngine.h"
#include "graphics/Shader.h"

//settings
constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 600;

//Function to set viewport
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

GameEngine::GameEngine(GLFWwindow * targetWindow)
    : m_window(targetWindow) {
    
    std::cout << "Initializing Engine." << std::endl;

    //Set context of the GLFWwindow
    glfwMakeContextCurrent(m_window);

    //used for user window resizing.
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    //Shaders
    m_shader = new Shader("../blue-tile-engine-lite/engine/graphics/glsl/Vertex.glsl", "../blue-tile-engine-lite/engine/graphics/glsl/Fragment.glsl");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GameEngine::~GameEngine() {
    std::cout << "Engine is deinitializing." << std::endl;
}

//TO-DO Delete this or move somewhere else.
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
    glViewport(0, 0, width, height);
}

Shader * GameEngine::getShader() {
    return m_shader;
}

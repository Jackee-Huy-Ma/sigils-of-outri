#include <memory>
#include <engine/GameWindow.h>
#include <engine/GameEngine.h>
#include <engine/graphics/Quad.h>
#include <engine/graphics/Shader.h>
#include <engine/GameObject.h>
#include <engine/graphics/Texture.h>
#include <glm/glm.hpp>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
int main() {
    GameWindow gameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    int windowSetupStatus = gameWindow.SetupGLFWwindow();

    if(windowSetupStatus) {
        std::cout <<"Failed to make window." << std::endl;
        return 1;
    }

    std::shared_ptr<GameEngine> engine = std::make_shared<GameEngine>(gameWindow.getWindow());
    
    GameObject * gameObject = new GameObject("Quad", glm::vec3(0), glm::vec3(0), glm::vec3(1), "../assets/main_character.png");
    
    while(!glfwWindowShouldClose(gameWindow.getWindow())) {
        engine->processEvent(gameWindow.getWindow());
        engine->update();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        gameObject->update();
        gameObject->setTransformMatrix(engine->m_ortho * gameObject->getTransformMatrix()); 
        gameObject->Draw(*(engine->getShader()));
        engine->draw();
    }
   
    return 0;
}
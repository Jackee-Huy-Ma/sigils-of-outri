#include <memory>
#include <engine/GameWindow.h>
#include <engine/GameEngine.h>

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
    
    while(!glfwWindowShouldClose(gameWindow.getWindow())) {
        engine->processEvent(gameWindow.getWindow());
        engine->update();
        engine->draw();
    }
   
    return 0;
}
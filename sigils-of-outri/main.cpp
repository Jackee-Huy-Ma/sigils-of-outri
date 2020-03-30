#include <memory>
#include <engine/GameWindow.h>
#include <engine/GameEngine.h>
#include <engine/graphics/Quad.h>
#include <engine/graphics/Shader.h>
#include <engine/GameObject.h>
#include <engine/graphics/Texture.h>
#include <engine/graphics/Camera.h>
#include <glm/glm.hpp>
#include "Player.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr float CAMERA_FOV = glm::radians(10.0f);
constexpr float CAMERA_NEAR_CLIP = 1.0f;
constexpr float CAMERA_FAR_CLIP = 2.0f;
int main() {
    GameWindow gameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    int windowSetupStatus = gameWindow.SetupGLFWwindow();

    if(windowSetupStatus) {
        std::cout <<"Failed to make window." << std::endl;
        return 1;
    }

    std::shared_ptr<GameEngine> engine = std::make_shared<GameEngine>(gameWindow.getWindow());

    //Camera Setup
    Camera::getInstance().setPosition(glm::vec3(0, 0, 0));
    Camera::getInstance().setPerspective(CAMERA_FOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

    
    //Draw order matters
    //character goes 2nd.
    //Sequences of vertices given.
    //layers.
    //Sudo code for today goal.
    //Want to Calculate the difference of position between camera and player
    // Total Distance to move camera to reach player: temp pos = (gameObject.position - camera.getInstance().position)
    // Time to travel this distance should be 0.5 senconds.
    // Velocity = d / t; constant velocity. pos / 0.5
    // If not statement(camera pos is > player position - threshod && camerapos < player position + threshold).
        // At each update(delta Time), translating Camera Position = velocity * deltaTime; D = V * T;
    //

    
    //GameObject * gameObject = new GameObject("Quad", glm::vec3(0), glm::vec3(0), glm::vec3(1), "../assets/main_character.png");
    
    Player * player = new Player("Quad", glm::vec3(0), glm::vec3(0), glm::vec3(1), "../assets/main_character.png");

    float previousTime = glfwGetTime();
    while(!glfwWindowShouldClose(gameWindow.getWindow())) {
        //Set Ortho.
        Camera::getInstance().setOrtho(gameWindow.getWindow());
        //engine->processEvent(gameWindow.getWindow());
        glfwPollEvents();
        
        if(glfwGetKey(gameWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(gameWindow.getWindow(), true);

        float currentTime = glfwGetTime();
        float delta = currentTime - previousTime;
        previousTime = glfwGetTime();
        
        engine->update();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        player->update(delta);
        player->setTransformMatrix(Camera::getInstance().getViewMatrix() * player->getTransformMatrix());
        player->setTransformMatrix(Camera::getInstance().getViewMatrix() * player->getTransformMatrix());
        player->setTransformMatrix(Camera::getInstance().getPerspective() * player->getTransformMatrix()); 
        player->Draw(*(engine->getShader()));
        engine->draw();
    }
   
    return 0;
}
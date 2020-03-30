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

constexpr float CAMERA_FOV = glm::radians(45.0f);
constexpr float CAMERA_NEAR_CLIP = 0.1f;
constexpr float CAMERA_FAR_CLIP = 3000.0f;
constexpr float THRESHOLD = 50.0f;
constexpr float CAMERA_TIME = 2.0f;

int main() {
    GameWindow gameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    int windowSetupStatus = gameWindow.SetupGLFWwindow();

    if(windowSetupStatus) {
        std::cout <<"Failed to make window." << std::endl;
        return 1;
    }

    std::shared_ptr<GameEngine> engine = std::make_shared<GameEngine>(gameWindow.getWindow());

    //Camera Setup
    Camera::getInstance().setPosition(glm::vec3(0, 0, 1500.0f));
    Camera::getInstance().setPerspective(CAMERA_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

    
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

        if(glfwGetKey(gameWindow.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            player->m_speed = 100.0f;
            player->m_velocity = glm::vec3(player->m_speed, 0, 0);
        }else {
            player->m_speed = 0.0f;
            player->m_velocity = glm::vec3(0);
        }


        glm::vec3 distance = glm::vec3(player->m_position - Camera::getInstance().getPosition());
        glm::vec3 c_velocity = glm::vec3(distance.x / CAMERA_TIME, distance.y / CAMERA_TIME, 0);
        float currentTime = glfwGetTime();
        float delta = currentTime - previousTime;
        previousTime = glfwGetTime();
        
        glm::vec3 c = Camera::getInstance().getPosition();
        if(!(c.x > player->m_position.x - THRESHOLD && c.y > player->m_position.y - THRESHOLD && c.x < player->m_position.x + THRESHOLD && c.y < player->m_position.y + THRESHOLD)) {
            glm::vec3 tempCameraPos = Camera::getInstance().getPosition();
            tempCameraPos += c_velocity * delta;
            Camera::getInstance().setPosition(tempCameraPos);
        }
        // At each update(delta Time), translating Camera Position = velocity * deltaTime; D = V * T;
        engine->update();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        player->update(delta);
        player->setTransformMatrix(Camera::getInstance().getViewMatrix() * player->getTransformMatrix());
        player->setTransformMatrix(Camera::getInstance().getPerspective() * player->getTransformMatrix()); 
        player->Draw(*(engine->getShader()));
        engine->draw();
    }
    //MOVE CAMERA THINGS INTO CAMERA.
    //Scale Player in Gameobject.cpp.
    //Fix Speed.
    //implement basic light.
    //TO-DO Wang's algorithm - Name generator & int generator, Make table.
    //Write Report.
    //Talk to borna.
    return 0;
}
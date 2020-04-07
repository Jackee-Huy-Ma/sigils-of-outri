#include <engine/GameWindow.h>
#include <engine/GameEngine.h>
#include <engine/graphics/Quad.h>
#include <engine/graphics/Shader.h>
#include <engine/GameObject.h>
#include <engine/graphics/Texture.h>
#include <engine/graphics/Camera.h>

#include <glm/glm.hpp>
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <memory>
#include <engine/SoundEngine.h>
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr float CAMERA_FOV = glm::radians(45.0f);
constexpr float CAMERA_NEAR_CLIP = 0.1f;
constexpr float CAMERA_FAR_CLIP = 100.0f;
constexpr float THRESHOLD = 5.0f;
constexpr float CAMERA_TIME = 1.25f;

int main() {
    //boolean used to equip gear once.
    bool isEquip = false;
    bool isBattle = false;
    GameWindow gameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    int windowSetupStatus = gameWindow.SetupGLFWwindow();

    if(windowSetupStatus) {
        std::cout <<"Failed to make window." << std::endl;
        return 1;
    }

    std::shared_ptr<GameEngine> engine = std::make_shared<GameEngine>(gameWindow.getWindow());

    //Camera Setup
    Camera::getInstance().setPosition(glm::vec3(0, 12.5f, 50.0f));
    Camera::getInstance().setPerspective(CAMERA_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);
    
    Player * player = new Player("Player", glm::vec3(0), glm::vec3(0), glm::vec3(0.025), "../assets/main_character.png");
    GameObject * background = new GameObject("Background", glm::vec3(0, 6, 0), glm::vec3(0), glm::vec3(0.17), "../assets/Capture.png");
    Enemy * boss = new Enemy("Boss", glm::vec3(15, 8, 0), glm::vec3(0), glm::vec3(0.05), "../assets/boss.png");

    float previousTime = glfwGetTime();

    SoundEngine * soundengine = new SoundEngine("../assets/game_music.wav");

    std::vector<GameObject *> list;

    list.push_back(boss);
    list.push_back(player);

    while(!glfwWindowShouldClose(gameWindow.getWindow())) {
        //Set Ortho.
        Camera::getInstance().setOrtho(gameWindow.getWindow());
        //engine->processEvent(gameWindow.getWindow());
        glfwPollEvents();
        
        if(glfwGetKey(gameWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(gameWindow.getWindow(), true);

        if(glfwGetKey(gameWindow.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if(player->m_rotation.x < 0)
                player->m_rotation.x = player->m_rotation.x * -1;
            player->m_speed = 25.0f;
            player->m_velocity = glm::vec3(player->m_speed, 0, 0);
        }else if(glfwGetKey(gameWindow.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            if(player->m_rotation.x > 0)
                player->m_rotation.x = player->m_rotation.x * -1;
            player->m_speed = -25.0f;
            player->m_velocity = glm::vec3(player->m_speed, 0, 0);    
        }else if((glfwGetKey(gameWindow.getWindow(), GLFW_KEY_E) == GLFW_PRESS) && isEquip == false) {
            isEquip = true;
            player->simulate(*player,*boss);
            player->autoEquip();
        }else {
            player->m_speed = 0.0f;
            player->m_velocity = glm::vec3(0);
        }

        //Delta Time
        float currentTime = glfwGetTime();
        float delta = currentTime - previousTime;
        previousTime = glfwGetTime();

        Camera::getInstance().followTarget(delta, CAMERA_TIME, THRESHOLD, player->m_position);
        
        engine->update();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        background->update(delta);
        background->Draw(*(engine->getShader()));
        for(int i = 0; i < list.size(); i++) {
            list[i]->update(delta);
            list[i]->Draw(*(engine->getShader()));
        }
        if(player->m_position.x >= boss->m_position.x && isBattle == false) {
            isBattle = true;
            std::cout << "Combat Engaged!" << std::endl;
            bool test = player->combat(*player, *boss);
            if(test == true) {
                list.erase(list.begin());
            }else {
                list.erase(list.begin() + 1);
            }
        }
        /*boss->update(delta);
        boss->Draw(*(engine->getShader()));
        player->update(delta);
        player->Draw(*(engine->getShader()));
        */
        engine->draw();
    }

    return 0;
}
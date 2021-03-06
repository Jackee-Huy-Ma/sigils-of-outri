#pragma once
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
class Shader;
class GameEngine {
public:
    //Constructor to game engine that takes a GLFWwindow
    GameEngine(GLFWwindow * targetWindow);

    //Deconstructor
    ~GameEngine();

    //Engine handles events from user
    void processEvent(GLFWwindow * targetwindow);

    //Main Loop for a game
    void update();

    //draw
    void draw();

    //Getter
    Shader * getShader();

    glm::mat4 m_ortho;

private:
    //Pointer to a GLFWwindow
    GLFWwindow * m_window;

    //Last time
    double m_previousTime = 0;

    //Current time
    double m_currentTime = 0;

    //Number of frames
    int m_frameCounter = 0;

    //function that updates fps counter
    void updateFPSCounter();

    //Shader Manager.
    Shader * m_shader;
};
#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
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

    //TODO
    //draw
    void draw();

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

};
#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class GameWindow {
public:
    GameWindow(int width, int height);
    ~GameWindow();
    int SetupGLFWwindow();
    GLFWwindow * getWindow();

private:
    // Pointer to GLFWwindow.
    GLFWwindow * m_window;

    // Width of the window
    int m_windowWidth;

    // Height of the window

    int m_windowHeight;

};
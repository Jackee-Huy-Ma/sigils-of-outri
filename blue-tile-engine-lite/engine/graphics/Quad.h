#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Quad {
public:
    //Default constructor
    Quad();

    //Deconstructor
    ~Quad();

    unsigned int m_VBO = 0;

    unsigned int m_VAO = 0;

    unsigned int m_EBO = 0;

    void draw();

private:
    std::vector<float> m_vertices;

    std::vector<unsigned int> m_indices;
};
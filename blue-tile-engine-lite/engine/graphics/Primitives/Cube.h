#pragma once
#include "../Vertex.h"
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Cube {
public:
    //Default constructor
    Cube();

    //Deconstructor
    ~Cube();

private:
     //List of Gluint
    std::vector<GLuint> m_indexList;

    //List of vertices
    std::vector<Vertex> m_vertexList;
    //private method used for initialization of the two vectors
    void initCube();

};
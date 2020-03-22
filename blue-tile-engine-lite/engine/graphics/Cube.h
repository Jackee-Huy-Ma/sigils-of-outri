#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Vertex;
class Cube {
public:
    //Default constructor
    Cube();

    //Deconstructor
    ~Cube();

    unsigned int VBO = 0;

    unsigned int VAO = 0;

private:
     //List of Gluint
    std::vector<float> m_indexList;

    //List of vertices
    std::vector<Vertex> m_vertexList;
    //private method used for initialization of the two vectors
    void initCube();

};
#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<iostream>

//Enum representing attributes of a vertex
enum vertexAttributes {
    position = 0,
    color = 1,
    texCoord = 2,
    normal = 3
};

class Vertex {
public:
    //Constructor Reads in data buids the m_vertexStruct data.
    Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v, GLfloat nx, GLfloat ny, GLfloat nz);
    
    //Deconstructor
    ~Vertex();
    
    //Getter function
    void getVertex();
private:
    //Position
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_z;

    //Colors
    GLfloat m_r;
    GLfloat m_g;
    GLfloat m_b;
    GLfloat m_a;

    //Textures
    GLfloat m_u;
    GLfloat m_v;

    //Normals
    GLfloat m_nx;
    GLfloat m_ny;
    GLfloat m_nz;

};

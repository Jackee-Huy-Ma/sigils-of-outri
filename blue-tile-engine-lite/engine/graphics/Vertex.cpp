#include "Vertex.h"

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v, GLfloat nx, GLfloat ny, GLfloat nz) {
    //Set Position
    m_x = x;
    m_y = y;
    m_z = z;

    //Set Colour
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;

    //Set Texture
    m_u = u;
    m_v = v;

    //Set Normals
    m_nx = nx;
    m_ny = ny;
    m_nz = nz;
}



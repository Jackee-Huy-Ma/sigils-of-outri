#include "Quad.h"

Quad::Quad() {
    m_vertices = {
        // positions         // colors
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f   // top 
    };

    m_indices = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_VAO);

    //Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices.front(), GL_STATIC_DRAW);
    
    //Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(float), &m_indices.front(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

}

Quad::~Quad() {
}

void::Quad::draw() {
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}

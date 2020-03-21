#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

class Shader;

class GameObject {
public:
    //Constructor takes in a name, position, rotation, scale
    GameObject(std::string name = "Default", glm::vec3 position = glm::vec3(0, 0, 0),
            glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
    
    //Deconstructor
    ~GameObject();

    //Update
    virtual void Update();

    //Draw
    virtual void draw();

    //Getter for Transform Matrix
    glm::mat4 getTransformMatrix();

    //Update Transform Matrix
    void updateTransformMatrix();

    //GameObject ID
    GLuint Id;

    //Name of GameObject
    std::string name;

    //Position of GameObject
    glm::vec3 position;

    //Rotation of GameObjec
    glm::vec3 rotation;

    //Scale of GameObject
    glm::vec3 scale;

    //Forward of GameObject
    glm::vec3 forward;

private:
    //Transform Matrix
    glm::mat4 m_transformMatrix;

    //Static id counter gets incremented
    static int idCounter;
};
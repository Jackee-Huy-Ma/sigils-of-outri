#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

class Quad;
class Shader;
class GameObject {
public:
    //Constructor takes in a name, position, rotation, scale, texture
    GameObject(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);    
    //Deconstructor
    ~GameObject();

    //Update
    //virtual void Update();

    //Draw
    void Draw(Shader& shader);
    
    //GameObject ID
    GLuint m_Id;

    //Name of GameObject
    std::string m_name;

    //Position of GameObject
    glm::vec3 m_position;

    //Rotation of GameObjec
    glm::vec3 m_rotation;

    //Scale of GameObject
    glm::vec3 m_scale;
   
    glm::mat4 getTransformMatrix();
    void setTransformMatrix(glm::mat4 transformMatrix);

    //Update Transform Matrix
    void updateTransformMatrix();

    //update
    virtual void update(float deltaTime);

    //draw
    void draw(Shader & shader);

    //Object's speed
    float m_speed = 0.0f;

    //Object's velocity if it has one.
    glm::vec3 m_velocity = glm::vec3(0);
private:
    //Forward of GameObject
    glm::vec3 m_forward;
    
    //Transform Matrix
    glm::mat4 m_transformMatrix;

    //Model of the GameObject
    //In this case just a cube
    Quad * m_mesh;

    //Static id counter gets incremented
    static int idCounter;
};
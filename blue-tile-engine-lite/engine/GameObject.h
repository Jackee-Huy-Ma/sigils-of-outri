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
    virtual void Draw(Shader& shader);
    //Getters
    /*GLuint getId();
    std::string getName();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getForward();
    glm::mat4 getTransformMatrix();

    //Setters
    void setId(GLuint id) const;
    void setName(std::string & name) const;
    void setPosition(glm::vec3 position) const;
    void setRotation(glm::vec3 rotation) const;
    void setForward(glm::vec3 forward) const;
    */
    //Update Transform Matrix
    //void updateTransformMatrix();

    //update
    void update(glm::vec2 windowSize);

    //draw
    void draw(Shader & shader);

private:
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
#pragma once
#include <glm/glm.hpp>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    //Deconstructor
    virtual ~Camera();

    //No Copying
    Camera(const Camera & oter ) = delete;
    Camera & operator = (const Camera & other) = delete;

    //Instance of the Camera
    static Camera & getInstance();

    //Set position via vec3
    void setPosition(const glm::vec3 & position);

    //Set orientation via vec3
    void setOrientation(const glm::vec3 & orientation);

    //Moves the camera via vec3
    void translate(const glm::vec3 & translation);

    //Get Position
    glm::vec3 getPosition() const;

    //Get Orientation
    glm::vec3 getOrientation() const;

    //Get Forward
    glm::vec3 getForward() const;

    //Get view matrix
    glm::mat4 getViewMatrix() const;

    //Get near and far clip
    //std::pair<float, float> getZclip() const;

private:
    //Constructor
    Camera();

    // set viewMatrix
    void setViewMatrix();

    //Position of camera
    glm::vec3 m_position;

    //Orientation of camera
    glm::vec3 m_orientation;

    //forward vector of camera
    glm::vec3 m_forward;
    
    //view matrix of camera
    glm::mat4 m_viewMatrix;
};
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include "../GameObject.h"
#include <iostream>
Camera::Camera()
    : m_position()
    , m_orientation()
    , m_viewMatrix() 
{
    setViewMatrix();
}

Camera::~Camera() {

}

Camera & Camera::getInstance() {
    static Camera instance;
    return instance;
}

void Camera::setPosition(const glm::vec3 & position) {
    m_position = position;
    setViewMatrix();
    //calculate viewMatrix;
}

void Camera::setOrientation(const glm::vec3 & orientation) {
    m_orientation = orientation;
    setViewMatrix();
}

void Camera::translate(const glm::vec3 & translation) {
    m_position += translation;
    setViewMatrix();
}

void Camera::setPerspective(const float fov, float aspect, const float nearClip, const float farClip) {
    m_clips.first = nearClip;
    m_clips.second = farClip;
    m_perspective = glm::perspective(fov, aspect, nearClip, farClip);
}
    
    
void Camera::setOrtho(GLFWwindow * window) {
    int height;
    int width;
    glfwGetWindowSize(window, &width, &height);
    m_ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
}

glm::vec3 Camera::getPosition() const {
    return m_position;
}

glm::vec3 Camera::getOrientation() const {
    return m_orientation;
}

glm::vec3 Camera::getForward() const {
    return m_forward;
}

glm::mat4 Camera::getViewMatrix() const {
    return m_viewMatrix;
}

std::pair<float, float> Camera::getZclip() const {
    return m_clips;
}

glm::mat4 Camera::getPerspective() const {
    return m_perspective;
}

glm::mat4 Camera::getOrtho() const {
    return m_ortho;
}

void Camera::setViewMatrix() {
    
    glm::quat rotationQuaternion = glm::quat(m_orientation);
    glm::mat4 rotationMatrix = glm::mat4(rotationQuaternion);

    m_forward = glm::normalize(glm::vec3(-rotationMatrix[0][2], -rotationMatrix[1][2], rotationMatrix[2][2]));

    //negative position
    glm::mat4 positionMatrix = glm::translate(glm::mat4(1), -m_position);

    m_viewMatrix = rotationMatrix * positionMatrix;
}

void Camera::followTarget(float delta, const float CAMERA_TIME, const float THRESHOLD, glm::vec3 & targetPosition) {
    //Distance between Target and Camera
    glm::vec3 distance = targetPosition - m_position;
    
    //Desired Velocity
    glm::vec3 camera_velocity = glm::vec3(distance.x / CAMERA_TIME, distance.y / CAMERA_TIME, 0);

    //Checks if Camera position is within a threshold.
    if(!(camera_velocity.x > targetPosition.x - THRESHOLD 
        && camera_velocity.y > targetPosition.y - THRESHOLD 
        && camera_velocity.x < targetPosition.x + THRESHOLD 
        && camera_velocity.y < targetPosition.y + THRESHOLD)) {
        m_position.x += camera_velocity.x * delta;
        setViewMatrix();
    }
}

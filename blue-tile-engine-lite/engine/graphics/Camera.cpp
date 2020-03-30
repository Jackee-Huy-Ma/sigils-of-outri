#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

Camera::Camera()
    : m_position()
    , m_orientation()
    , m_viewMatrix() 
{
}

Camera::~Camera() {

}

Camera & Camera::getInstance() {
    static Camera instance;
    return instance;
}

void Camera::setPosition(const glm::vec3 & position) {
    m_position = position;
    //calculate viewMatrix;
}

void Camera::setOrientation(const glm::vec3 & orientation) {
    m_orientation = orientation;
    //viewmatrix
}

void Camera::translate(const glm::vec3 & translation) {
    m_position += translation;

    //viewmatrix
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

void Camera::setViewMatrix() {
    
    glm::quat rotationQuaternion = glm::quat(m_orientation);
    glm::mat4 rotationMatrix = glm::mat4(rotationQuaternion);

    m_forward = glm::normalize(glm::vec3(-rotationMatrix[0][2], -rotationMatrix[1][2], rotationMatrix[2][2]));

    //negative position
    glm::mat4 positionMatrix = glm::translate(glm::mat4(1), -m_position);

    m_viewMatrix = rotationMatrix * positionMatrix;
}

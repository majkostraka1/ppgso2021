#include "camera.h"
#include "scene.h"


Camera::Camera(float fov, float ratio, float near, float far) {
    projectionMatrix = glm::perspective(glm::radians(fov), ratio, near, far);
}


void Camera::handleCursor(Cursor cursor) {

    glm::vec3 front;
    float yaw = cursor.yaw;
    float pitch = cursor.pitch;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->back = -glm::normalize(front);
}


// NOTE: in "player" class, the camera position is set to the player position
void Camera::update(Scene &scene, float dTime) {
    handleCursor(scene.cursor);
    position += back * 5.f;

    std:std::cout<<position.x << " " << position.y << " " << position.z<<std::endl;

    viewMatrix = lookAt(position, position - back, up);
}


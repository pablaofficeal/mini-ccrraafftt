#include "camera.h"
#include <GL/gl.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Переменные состояния камеры (статические, чтобы быть видимыми только в этом файле)
static glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
static float cameraPitch = -10.0f;
static float cameraYaw = 0.0f;

// Переменные состояния мыши для управления камерой
static float lastX = 400, lastY = 300;
static bool firstMouse = true;

// Более точное значение PI
const float M_PI_F = 3.14159265358979323846f;

void updateCamera(const bool keys[]) {
    float speed = 0.1f;
    
    // Рассчитываем векторы для движения вперед/вбок без учета вертикального наклона
    glm::vec3 front;
    front.x = cos(glm::radians(cameraYaw));
    front.z = sin(glm::radians(cameraYaw));
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (keys['w']) {
        // Движение вперед относительно направления камеры по горизонтали
        cameraPos.x += sin(glm::radians(cameraYaw)) * speed;
        cameraPos.z -= cos(glm::radians(cameraYaw)) * speed;
    }
    if (keys['s']) {
        cameraPos.x -= sin(glm::radians(cameraYaw)) * speed;
        cameraPos.z += cos(glm::radians(cameraYaw)) * speed;
    }
    if (keys['a']) {
        cameraPos -= right * speed;
    }
    if (keys['d']) {
        cameraPos += right * speed;
    }
    if (keys[' ']) {
        cameraPos.y += speed;
    }
    if (keys['c']) {
        cameraPos.y -= speed;
    }
}

void processMouseMovement(float x, float y) {
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cameraYaw += xoffset;
    cameraPitch += yoffset;

    if (cameraPitch > 89.0f) cameraPitch = 89.0f;
    if (cameraPitch < -89.0f) cameraPitch = -89.0f;
}

glm::mat4 getViewMatrix() {
    glm::vec3 front;
    front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    front.y = sin(glm::radians(cameraPitch));
    front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    glm::vec3 cameraFront = glm::normalize(front);

    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
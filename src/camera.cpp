#include "camera.h"
#include <GL/gl.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Константы для управления камерой и ограничениями
const float MOVEMENT_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.1f;
const float YAW_TURN_SPEED_MULTIPLIER = 10.0f;
const float MAX_PITCH = 89.0f;
const float MIN_PITCH = -89.0f;
const float WORLD_BOUNDARY = 100.0f;
const float MIN_HEIGHT = 0.0f;
const float MAX_HEIGHT = 100.0f;

// Переменные состояния камеры (статические, чтобы быть видимыми только в этом файле)
static glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
static float cameraPitch = -10.0f;
static float cameraYaw = 0.0f;

// Переменные состояния мыши для управления камерой
static float lastX = 400, lastY = 300;
static bool firstMouse = true;

void updateCamera(const bool keys[]) {
    // Рассчитываем векторы для движения вперед/вбок, основываясь только на рыскании (yaw)
    // Это создает "летающий" стиль управления, где наклон (pitch) не влияет на плоскость движения
    glm::vec3 front_horizontal;
    front_horizontal.x = cos(glm::radians(cameraYaw));
    front_horizontal.y = 0.0f; // Движение строго по горизонтали
    front_horizontal.z = sin(glm::radians(cameraYaw));
    front_horizontal = glm::normalize(front_horizontal);

    glm::vec3 right = glm::normalize(glm::cross(front_horizontal, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (keys['w']) {
        // Движение вперед. Этот код более стандартный: cameraPos += front * speed.
        cameraPos += front_horizontal * MOVEMENT_SPEED;
    }
    if (keys['s']) {
        cameraPos -= front_horizontal * MOVEMENT_SPEED;
    }
    if (keys['a']) {
        cameraPos -= right * MOVEMENT_SPEED;
    }
    if (keys['d']) {
        cameraPos += right * MOVEMENT_SPEED;
    }
    if (keys[' ']) {
        cameraPos.y += MOVEMENT_SPEED;
    }
    if (keys['c']) {
        cameraPos.y -= MOVEMENT_SPEED;
    }
    if (keys['q']) {
        cameraYaw -= MOVEMENT_SPEED * YAW_TURN_SPEED_MULTIPLIER; // Поворот влево
    }
    if (keys['e']) {
        cameraYaw += MOVEMENT_SPEED * YAW_TURN_SPEED_MULTIPLIER; // Поворот вправо
    }
/*
    // поворот камеры в низ
    if (keys['z']) {
        cameraPitch -= MOVEMENT_SPEED * YAW_TURN_SPEED_MULTIPLIER; // Поворот вниз
    }
    // поворот камеры в верх
    if (keys['x']) {
        cameraPitch += MOVEMENT_SPEED * YAW_TURN_SPEED_MULTIPLIER; // Поворот вверх
    }
*/
    // Нормализация угла рыскания (yaw)
    cameraYaw = fmod(cameraYaw, 360.0f);
    if (cameraYaw < 0.0f) {
        cameraYaw += 360.0f;
    }

    // Ограничение угла наклона (pitch)
    if (cameraPitch > MAX_PITCH) cameraPitch = MAX_PITCH;
    if (cameraPitch < MIN_PITCH) cameraPitch = MIN_PITCH;

    // Ограничение позиции камеры в пределах мира
    cameraPos.x = glm::clamp(cameraPos.x, -WORLD_BOUNDARY, WORLD_BOUNDARY);
    cameraPos.y = glm::clamp(cameraPos.y, MIN_HEIGHT, MAX_HEIGHT);
    cameraPos.z = glm::clamp(cameraPos.z, -WORLD_BOUNDARY, WORLD_BOUNDARY);
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

    xoffset *= MOUSE_SENSITIVITY;
    yoffset *= MOUSE_SENSITIVITY;

    cameraYaw += xoffset;
    cameraPitch += yoffset;

    if (cameraPitch > MAX_PITCH) cameraPitch = MAX_PITCH;
    if (cameraPitch < MIN_PITCH) cameraPitch = MIN_PITCH;
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

glm::vec3 getCameraPos() {
    return cameraPos;
}
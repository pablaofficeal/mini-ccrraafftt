#include "camera.h"
#include <GL/gl.h>
#include <cmath>

// Переменные состояния камеры (статические, чтобы быть видимыми только в этом файле)
static float cameraX = 0.0f;
static float cameraY = 1.0f;
static float cameraZ = 3.0f;
static float cameraPitch = -10.0f;
static float cameraYaw = 0.0f;

// Переменные состояния мыши для управления камерой
static float lastX = 400, lastY = 300;
static bool firstMouse = true;

// Более точное значение PI
const float M_PI_F = 3.14159265358979323846f;

void updateCamera(const bool keys[]) {
    float speed = 0.1f;
    float yawRad = cameraYaw * M_PI_F / 180.0f;

    if (keys['w']) {
        cameraX += sin(yawRad) * speed;
        cameraZ -= cos(yawRad) * speed;
    }
    if (keys['s']) {
        cameraX -= sin(yawRad) * speed;
        cameraZ += cos(yawRad) * speed;
    }
    if (keys['a']) {
        cameraX -= cos(yawRad) * speed;
        cameraZ -= sin(yawRad) * speed;
    }
    if (keys['d']) {
        cameraX += cos(yawRad) * speed;
        cameraZ += sin(yawRad) * speed;
    }
    if (keys[' ']) {
        cameraY += speed;
    }
    if (keys['c']) {
        cameraY -= speed;
    }
}

void applyCameraView() {
    glRotatef(-cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-cameraYaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);
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
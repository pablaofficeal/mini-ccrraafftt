#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

// Обновляет позицию камеры на основе нажатых клавиш
void updateCamera(const bool keys[]);

// Возвращает матрицу вида (view matrix) для использования в шейдере
glm::mat4 getViewMatrix();

// Обрабатывает движение мыши для обновления ориентации камеры
void processMouseMovement(float x, float y);

#endif // CAMERA_H
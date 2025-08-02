#ifndef CAMERA_H
#define CAMERA_H

// Обновляет позицию камеры на основе нажатых клавиш
void updateCamera(const bool keys[]);

// Применяет трансформации вида камеры (view transformations)
void applyCameraView();

// Обрабатывает движение мыши для обновления ориентации камеры
void processMouseMovement(float x, float y);

#endif // CAMERA_H
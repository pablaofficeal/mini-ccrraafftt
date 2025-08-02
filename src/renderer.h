#ifndef RENDERER_H
#define RENDERER_H

// Инициализирует рендерер (VBO, шейдеры)
void initRenderer();

// Основная функция отрисовки, регистрируется как display func в GLUT
void drawWorld();

#endif // RENDERER_H
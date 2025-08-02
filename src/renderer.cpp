#include "renderer.h"
#include "camera.h"
#include "input.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Вспомогательная функция для отрисовки одного куба (статическая, не видна вне этого файла)
static void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);

    // Передняя грань (красная)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Задняя грань (зеленая)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Левая грань (синяя)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Правая грань (желтая)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Верхняя грань (пурпурная)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Нижняя грань (голубая)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();

    glPopMatrix();
}

void drawWorld() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Обновляем позицию камеры на основе ввода
    updateCamera(getKeyboardState());

    // Настраиваем матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Применяем трансформации камеры
    applyCameraView();

    // Рисуем землю
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();

    // Рисуем кубы
    drawCube(0.0f, 0.5f, 0.0f);
    drawCube(2.0f, 0.5f, 2.0f);
    drawCube(-2.0f, 0.5f, -2.0f);
    drawCube(3.0f, 1.5f, -1.0f);
    drawCube(-3.0f, 0.5f, 1.0f);

    glutSwapBuffers();
}
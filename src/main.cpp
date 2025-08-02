#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib> // Для exit()

#include "renderer.h"
#include "input.h"

void update(int value) {
    (void)value; // Подавляем предупреждение о неиспользуемом параметре
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void initOpenGL() {
    // Инициализация GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Ошибка инициализации GLEW: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Настраиваем обработчики событий из нашего модуля ввода
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutPassiveMotionFunc(mouseFunc);
    glutMotionFunc(mouseFunc);
    
    // Захватываем мышь
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Сцена с кубами (Модульная)");
    
    initOpenGL();
    
    // Устанавливаем функцию отрисовки из нашего модуля рендерера
    glutDisplayFunc(drawWorld);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}


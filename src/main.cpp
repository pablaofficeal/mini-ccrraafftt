#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib> 
#include <ctime>   // для time()
 
#include "renderer.h"
#include "input.h"
#include "world.h"


void update(int value) {
    (void)value;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void initOpenGL() {
    // Важно: GLEW должен быть инициализирован до вызова любых других функций OpenGL
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Ошибка инициализации GLEW: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Инициализируем наш рендерер (создаем VBO, шейдеры и т.д.)
    initRenderer();
    
    // Настраиваем обработчики событий из нашего модуля ввода
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutPassiveMotionFunc(mouseFunc);
    glutMotionFunc(mouseFunc);
    
    // Захватываем мышь
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char** argv) {
    // Инициализируем генератор случайных чисел
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("mini-ccrraafftt");
    
    initOpenGL();
    
    // Устанавливаем функцию отрисовки из нашего модуля рендерера
    glutDisplayFunc(drawWorld);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}

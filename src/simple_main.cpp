#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Переменные камеры
float cameraX = 0.0f;
float cameraY = 1.0f;
float cameraZ = 3.0f;
float cameraPitch = -10.0f;
float cameraYaw = 0.0f;

// Переменные для управления камерой
bool keys[256] = {false};
float lastX = 400, lastY = 300;
bool firstMouse = true;

void keyboardFunc(unsigned char key, int x, int y) {
    keys[key] = true;
    std::cout << "Клавиша нажата: " << key << std::endl;
    
    if (key == 27) { // ESC
        exit(0);
    }
}

void keyboardUpFunc(unsigned char key, int x, int y) {
    keys[key] = false;
}

void mouseFunc(int x, int y) {
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
    
    std::cout << "Мышь: x=" << x << " y=" << y << " yaw=" << cameraYaw << " pitch=" << cameraPitch << std::endl;
}

void updateCamera() {
    float speed = 0.1f;
    
    if (keys['w']) {
        cameraX += sin(cameraYaw * 3.14159f / 180.0f) * speed;
        cameraZ -= cos(cameraYaw * 3.14159f / 180.0f) * speed;
    }
    if (keys['s']) {
        cameraX -= sin(cameraYaw * 3.14159f / 180.0f) * speed;
        cameraZ += cos(cameraYaw * 3.14159f / 180.0f) * speed;
    }
    if (keys['a']) {
        cameraX -= cos(cameraYaw * 3.14159f / 180.0f) * speed;
        cameraZ -= sin(cameraYaw * 3.14159f / 180.0f) * speed;
    }
    if (keys['d']) {
        cameraX += cos(cameraYaw * 3.14159f / 180.0f) * speed;
        cameraZ += sin(cameraYaw * 3.14159f / 180.0f) * speed;
    }
    if (keys[' ']) {
        cameraY += speed;
    }
    if (keys['c']) {
        cameraY -= speed;
    }
}

void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    // Рисуем куб без шейдеров
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
    
    // Обновляем позицию камеры
    updateCamera();
    
    // Настраиваем матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Применяем трансформации камеры
    glRotatef(-cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-cameraYaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    
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

void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void initOpenGL() {
    std::cout << "Инициализация OpenGL..." << std::endl;
    
    // Инициализация GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Ошибка GLEW: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    
    std::cout << "GLEW инициализирован успешно" << std::endl;
    std::cout << "OpenGL версия: " << glGetString(GL_VERSION) << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    // Настраиваем обработчики событий
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutPassiveMotionFunc(mouseFunc);
    glutMotionFunc(mouseFunc);
    
    // Захватываем мышь
    glutSetCursor(GLUT_CURSOR_NONE);
    
    std::cout << "OpenGL инициализирован успешно" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Запуск упрощенной версии..." << std::endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Упрощенная 3D сцена");
    
    initOpenGL();
    
    glutDisplayFunc(drawWorld);
    glutTimerFunc(0, update, 0);
    
    std::cout << "Приложение запущено!" << std::endl;
    std::cout << "Управление: WASD - движение, мышь - поворот, ESC - выход" << std::endl;
    
    glutMainLoop();
    return 0;
} 
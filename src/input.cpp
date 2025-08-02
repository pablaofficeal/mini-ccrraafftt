#include "input.h"
#include "camera.h" // Необходимо для вызова processMouseMovement
#include <GL/glut.h> // Для exit()
#include <cstdlib>   // Для exit()

// Состояние ввода (статическое, чтобы быть видимым только в этом файле)
static bool keys[256] = {false};

void keyboardFunc(unsigned char key, int x, int y) {
    (void)x; (void)y;
    keys[key] = true;

    if (key == 27) { // ESC
        exit(0);
    }
}

void keyboardUpFunc(unsigned char key, int x, int y) {
    (void)x; (void)y;
    keys[key] = false;
}

void mouseFunc(int x, int y) {
    processMouseMovement(x, y);
}

const bool* getKeyboardState() {
    return keys;
}
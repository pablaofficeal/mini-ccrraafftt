#ifndef INPUT_H
#define INPUT_H

// Функции обратного вызова GLUT для обработки ввода
void keyboardFunc(unsigned char key, int x, int y);
void keyboardUpFunc(unsigned char key, int x, int y);
void mouseFunc(int x, int y);

// Предоставляет доступ к состоянию клавиатуры
const bool* getKeyboardState();

#endif // INPUT_H
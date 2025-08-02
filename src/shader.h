#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

// Функция для создания шейдерной программы из файлов с исходным кодом
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);

#endif // SHADER_H
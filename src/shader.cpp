#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Вспомогательная функция для проверки ошибок компиляции/линковки
void checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ОШИБКА::КОМПИЛЯЦИЯ_ШЕЙДЕРА типа: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ОШИБКА::ЛИНКОВКА_ПРОГРАММЫ типа: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath) {
    // 1. Получаем исходный код шейдеров из файлов
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Убеждаемся, что ifstream объекты могут выкидывать исключения
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Читаем содержимое файлов в потоки
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();
        // Конвертируем потоки в string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ОШИБКА::ШЕЙДЕР::ФАЙЛ НЕ ПРОЧИТАН: " << e.what() << std::endl;
        return 0;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Компилируем шейдеры
    GLuint vertex, fragment;

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // 3. Линкуем шейдерную программу
    GLuint ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Удаляем шейдеры, так как они уже не нужны после линковки
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return ID;
}
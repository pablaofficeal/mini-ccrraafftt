#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "shader.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib> // для rand()

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Глобальные переменные для ID объектов OpenGL
static GLuint cubeVAO, cubeVBO;
static GLuint groundVAO, groundVBO;
static GLuint shaderProgram;

// Простая структура для хранения данных о кубе
struct Cube {
    float x, y, z;
};

// Вектор для хранения всех кубов в нашем мире
static std::vector<Cube> worldCubes;
// Флаг, чтобы убедиться, что мы генерируем мир только один раз
static bool worldGenerated = false;

// Функция для процедурной генерации мира (forward declaration)
static void generateWorld();

void initRenderer() {
    // Создаем и компилируем нашу шейдерную программу
    shaderProgram = createShaderProgram("src/shaders/simple.vert", "src/shaders/simple.frag");

    // Настройки OpenGL
    glEnable(GL_CULL_FACE); // Включаем отсечение невидимых граней

    // Данные вершин для куба (позиция + цвет) - 36 вершин (6 граней * 2 треугольника * 3 вершины)
    float cubeVertices[] = {
        // positions          // colors
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, // cyan
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // red
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // red
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // yellow
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // blue
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // green
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,


            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // magenta
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,


        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // magenta
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,


        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // magenta
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,


        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // yellow
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,


        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // yellow
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

        
    };

    // Настройка VAO и VBO для куба
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Атрибут позиции
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Атрибут цвета
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Данные для земли
    float groundSize = 30.0f;
    float groundVertices[] = {
        // positions            // colors
        -groundSize, 0.0f, -groundSize,  0.3f, 0.5f, 0.3f,
         groundSize, 0.0f, -groundSize,  0.3f, 0.5f, 0.3f,
        -groundSize, 0.0f,  groundSize,  0.3f, 0.5f, 0.3f,

         groundSize, 0.0f, -groundSize,  0.3f, 0.5f, 0.3f,
         groundSize, 0.0f,  groundSize,  0.3f, 0.5f, 0.3f,
        -groundSize, 0.0f,  groundSize,  0.3f, 0.5f, 0.3f
    };

    for (int i = 18; i < 54; ++i) {
        groundVertices[i] = 0.0f; // Инициализируем остальные вершины нулями
    }
    {
    // Добавляем дополнительные вершины для земли, чтобы она была более сложной
    groundVertices[18] = -groundSize; // x
    groundVertices[19] = 0.0f; // y
    groundVertices[20] = -groundSize; // z
    groundVertices[21] = 0.3f; // r
    groundVertices[22] = 0.5f; // g
    groundVertices[23] = 0.3f; // b

    groundVertices[24] = groundSize; // x
    groundVertices[25] = 0.0f; // y
    groundVertices[26] = groundSize; // z
    groundVertices[27] = 0.3f; // r
    groundVertices[28] = 0.5f; // g
    groundVertices[29] = 0.3f; // b
    groundVertices[30] =  groundSize; // x
    groundVertices[31] = 0.0f; // y
    groundVertices[32] = -groundSize; // z
    groundVertices[33] = 0.3f; // r
    groundVertices[34] = 0.5f; // g
    groundVertices[35] = 0.3f; // b

    // Другие вершины для земли
    groundVertices[36] = -groundSize; // x
    groundVertices[37] = 0.0f; // y
    groundVertices[38] = -groundSize; // z
    groundVertices[39] = 0.3f; // r
    groundVertices[40] = 0.5f; // g
    groundVertices[41] = 0.3f; // b
    groundVertices[42] = groundSize; // x
    groundVertices[43] = 0.0f; // y
    groundVertices[44] = groundSize; // z
    groundVertices[45] = 0.3f; // r
    groundVertices[46] = 0.5f; // g
    groundVertices[47] = 0.3f; // b
    groundVertices[48] = groundSize; // x
    groundVertices[49] = 0.0f; // y
    groundVertices[50] = -groundSize; // z
    groundVertices[51] = 0.3f; // r
    groundVertices[52] = 0.5f; // g
    groundVertices[53] = 0.3f; // b


    groundVertices[54] = -groundSize; // x
    groundVertices[55] = 0.0f; // y
    groundVertices[56] = groundSize; // z
    groundVertices[57] = 0.3f; // r
    groundVertices[58] = 0.5f; // g
    groundVertices[59] = 0.3f; // b
    groundVertices[60] = groundSize; // x
    groundVertices[61] = 0.0f; // y
    groundVertices[62] = groundSize; // z
    groundVertices[63] = 0.3f; // r
    groundVertices[64] = 0.5f; // g
    groundVertices[65] = 0.3f; // b
    };

    // 

    // Создаем VAO и VBO для земли
    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);
    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
    // Атрибут позиции для земли
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Атрибут цвета для земли
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Генерируем мир (колонны из кубов)
    generateWorld();
    worldGenerated = true;

    // Устанавливаем начальное состояние камеры
    updateCamera(getKeyboardState());
    glutPostRedisplay();
    // Устанавливаем функцию отрисовки
    glutDisplayFunc(drawWorld);
    // Устанавливаем функцию обновления
    glutIdleFunc(drawWorld);
}

// Функция для процедурной генерации мира
static void generateWorld() {
    const int worldSize = 40; // Генерируем сетку 40x40
    const float spacing = 1.0f; // Расстояние между центрами кубов

    for (int i = -worldSize / 2; i < worldSize / 2; ++i) {
        for (int j = -worldSize / 2; j < worldSize / 2; ++j) {
            // Используем rand() для определения, следует ли размещать здесь колонну
            if (rand() % 8 == 0) { // Шанс 1 из 8 на создание колонны
                float x = i * spacing;
                float z = j * spacing;
                // Случайная высота для колонны из кубов
                int columnHeight = 1 + (rand() % 6); // Высота от 1 до 6 кубов
                for (int h = 0; h < columnHeight; ++h) {
                    worldCubes.push_back({x, 0.5f + (float)h, z});
                }
            }
        }
    }
}

const std::vector<Cube>& getGeneratedCubes() {
    return worldCubes;
}

// Основная функция отрисовки, регистрируется как display func в GLUT

void drawWorld() {
    // Генерируем мир при первом вызове
    if (!worldGenerated) {
        generateWorld();
        worldGenerated = true;
    }

    // Обновляем позицию камеры на основе ввода
    updateCamera(getKeyboardState());

    // Очистка экрана
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Активируем шейдерную программу
    glUseProgram(shaderProgram);

    // Создаем матрицы вида и проекции
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = getViewMatrix();

    // Передаем матрицы в шейдер
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

    // Рисуем землю
    glBindVertexArray(groundVAO);
    glm::mat4 model = glm::mat4(1.0f); // Матрица модели (единичная)
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Рисуем все кубы из нашего сгенерированного мира
    glBindVertexArray(cubeVAO);
    for (const auto& cube : worldCubes) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(cube.x, cube.y, cube.z));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
    glutSwapBuffers();
}

void cleanupRenderer() {
    // Освобождаем ресурсы OpenGL
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &groundVAO);
    glDeleteBuffers(1, &groundVBO);
    glDeleteProgram(shaderProgram);
}


void setWorldGenerated(bool generated) {
    worldGenerated = generated;
}
bool isWorldGenerated() {
    return worldGenerated;
}

void setWorldCubes(const std::vector<Cube>& cubes) {
    worldCubes = cubes;
}
const std::vector<Cube>& getWorldCubes() {
    return worldCubes;
}
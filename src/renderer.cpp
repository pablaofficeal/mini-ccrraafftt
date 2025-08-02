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
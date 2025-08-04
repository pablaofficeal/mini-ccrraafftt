#include "world.h"
#include <cstdlib> // Для rand()
#include <glm/glm.hpp> // Для glm::vec2, glm::vec3
#include <vector>

// Определение статических переменных, объявленных в world.h
std::vector<Cube> World::worldCubes;
bool World::worldGenerated = false;

// Реализация шума Перлина
// Источник: https://mrl.nyu.edu/~perlin/noise/
// Переработан для просто/generate используй шум перлина для генерации мираты и использования в данном контексте
namespace PerlinNoise {
    static const int P_SIZE = 256;
    static int p[P_SIZE * 2]; // Permutation table
    static glm::vec2 grad[P_SIZE]; // Gradients

    // Инициализация таблицы перестановок и градиентов
    void init() {
        for (int i = 0; i < P_SIZE; ++i) {
            p[i] = i;
            // Случайные градиенты для 2D шума
            float angle = glm::two_pi<float>() * (static_cast<float>(rand()) / RAND_MAX);
            grad[i] = glm::vec2(cos(angle), sin(angle));
        }

        // Перемешивание таблицы перестановок
        for (int i = 0; i < P_SIZE; ++i) {
            int swap_idx = rand() % P_SIZE;
            int tmp = p[i];
            p[i] = p[swap_idx];
            p[swap_idx] = tmp;
        }
        // Удвоение таблицы для удобства интерполяции
        for (int i = 0; i < P_SIZE; ++i) {
            p[i + P_SIZE] = p[i];
        }
    }

    // Вспомогательная функция для интерполяции
    float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // Вспомогательная функция для линейной интерполяции
    float lerp(float t, float a, float b) {
        return a + t * (b - a);
    }
    // Функция для получения значения шума Перлина
    float noise(float x, float y) {
        int X = static_cast<int>(floor(x)) & 255;
        int Y = static_cast<int>(floor(y)) & 255;
        x -= floor(x);
        y -= floor(y);
        float u = fade(x);
        float v = fade(y);
        int A = p[X] + Y;
        int AA = p[A];
        int AB = p[A + 1];
        int B = p[X + 1] + Y;
        int BA = p[B];
        int BB = p[B + 1];
        float result = lerp(v, lerp(u, glm::dot(grad[AA], glm::vec2(x, y)),
                                    glm::dot(grad[BA], glm::vec2(x - 1, y))),
                            lerp(u, glm::dot(grad[AB], glm::vec2(x, y - 1)),
                                    glm::dot(grad[BB], glm::vec2(x - 1, y - 1))));
        return result;
    }

        // Перемешивание таблицы перестановок
        for (int i = 0; i < P_SIZE; ++i) {
            int swap_idx = rand() % P_SIZE;
            int tmp = p[i];
            p[i] = p[swap_idx];
            p[swap_idx] = tmp;
        }
        // Удвоение таблицы для удобства интерполяции
        for (int i = 0; i < P_SIZE; ++i) {
            p[i + P_SIZE] = p[i];
        }
    }

    // Вспомогательная функция для интерполяции
    float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // Вспомогательная функция для линейной интерполяции
    float lerp(float t, float a, float b) {#include "world.h"
        return a + t * (b - a);
    }

    // Инициализация таблицы перестановок и градиентов
    void init() {
        for (int i = 0; i < P_SIZE; ++i) {
            p[i] = i;
            // Случайные градиенты для 2D шума
            float angle = glm::two_pi<float>() * (static_cast<float>(rand()) / RAND_MAX);
            grad[i] = glm::vec2(cos(angle), sin(angle));
        }

        // Перемешивание таблицы перестановок
        for (int i = 0; i < P_SIZE; ++i) {
            int swap_idx = rand() % P_SIZE;
            int tmp = p[i];
            p[i] = p[swap_idx];
            p[swap_idx] = tmp;
        }
        // Удвоение таблицы для удобства интерполяции
        for (int i = 0; i < P_SIZE; ++i) {
            p[i + P_SIZE] = p[i];
        }
    }

    // Вспомогательная функция для интерполяции
    float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // Вспомогательная функция для линейной интерполяции
    float lerp(float t, float a, float b) {
        return a + t * (b - a);
    }

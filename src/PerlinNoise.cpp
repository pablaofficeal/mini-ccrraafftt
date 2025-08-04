
#include "PerlinNoise.h"
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <cmath>

PerlinNoise::PerlinNoise(unsigned int seed) {
    // Инициализация генератора случайных чисел
    std::mt19937 gen(seed);

    // Создание вектора от 0 до 255
    std::vector<int> p_temp(P_SIZE);
    std::iota(p_temp.begin(), p_temp.end(), 0);

    // Перемешивание вектора
    std::shuffle(p_temp.begin(), p_temp.end(), gen);

    // Копирование и дублирование в массив p
    for (int i = 0; i < P_SIZE; ++i) {
        p[i] = p[i + P_SIZE] = p_temp[i];
    }
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoise::noise(double x, double y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;

    x -= floor(x);
    y -= floor(y);

    double u = fade(x);
    double v = fade(y);

    int A = p[X] + Y;
    int AA = p[A];
    int AB = p[A + 1];
    int B = p[X + 1] + Y;
    int BA = p[B];
    int BB = p[B + 1];

    double res = lerp(v, lerp(u, grad(p[AA], x, y), grad(p[BA], x - 1, y)),
                      lerp(u, grad(p[AB], x, y - 1), grad(p[BB], x - 1, y - 1)));
    return (res + 1.0) / 2.0; // Нормализация в диапазон [0, 1]
}

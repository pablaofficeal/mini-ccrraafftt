
#ifndef PERLINNOISE_H
#define PERLINNOISE_H

class PerlinNoise {
public:
    // Конструктор, который инициализирует шум с помощью сида
    PerlinNoise(unsigned int seed);
    // Функция для получения значения 2D шума
    double noise(double x, double y);

private:
    static const int P_SIZE = 256;
    int p[P_SIZE * 2]; // Таблица перестановок

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y);
};

#endif // PERLINNOISE_H

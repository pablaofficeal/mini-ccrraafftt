#ifndef WORLD_H
#define WORLD_H

#include <vector>

// Простая структура для хранения данных о кубе
struct Cube {
    float x, y, z;
};

// Класс для управления миром (генерация, хранение кубов)
class World {
public:
    // Генерирует кубы для мира
    static void generateWorld();

    // Возвращает константную ссылку на вектор сгенерированных кубов
    static const std::vector<Cube>& getGeneratedCubes();

private:
    // Вектор для хранения всех кубов в нашем мире
    static std::vector<Cube> worldCubes;
    // Флаг, чтобы убедиться, что мы генерируем мир только один раз
    static bool worldGenerated;
};

#endif // WORLD_H

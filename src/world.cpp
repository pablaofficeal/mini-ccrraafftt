#include "world.h"
#include <cstdlib> // Для rand()

// Определение статических переменных, объявленных в world.h
std::vector<Cube> World::worldCubes;
bool World::worldGenerated = false;

void World::generateWorld() {
    if (worldGenerated) {
        return; // Мир уже сгенерирован
    }

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
    worldGenerated = true;
}

const std::vector<Cube>& World::getGeneratedCubes() {
    return worldCubes;
}

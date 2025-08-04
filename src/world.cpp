
#include "world.h"
#include "PerlinNoise.h"

// Определение статических переменных, объявленных в world.h
std::vector<Cube> World::worldCubes;
bool World::worldGenerated = false;

void World::generateWorld(unsigned int seed) {
    if (worldGenerated) {
        return; // Мир уже сгенерирован
    }

    PerlinNoise perlin(seed);
    const int worldSize = 40; // Генерируем сетку 40x40
    const double frequency = 0.1; // Частота шума
    const int maxHeight = 10; // Максимальная высота ландшафта

    for (int i = -worldSize / 2; i < worldSize / 2; ++i) {
        for (int j = -worldSize / 2; j < worldSize / 2; ++j) {
            double value = perlin.noise(i * frequency, j * frequency);
            int height = static_cast<int>(value * maxHeight);

            for (int h = 0; h < height; ++h) {
                worldCubes.push_back({(float)i, (float)h + 0.5f, (float)j});
            }
        }
    }
    worldGenerated = true;
}


const std::vector<Cube>& World::getGeneratedCubes() {
    return worldCubes;
}

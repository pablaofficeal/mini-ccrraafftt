# PVO OpenGL Project

Проект с использованием OpenGL для создания 3D сцены с кубами.
**Решена проблема совместимости с Wayland!**

## Зависимости

Для компиляции проекта необходимы следующие библиотеки:

### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libglew-dev freeglut3-dev libgl1-mesa-dev
```

### CentOS/RHEL/Fedora:
```bash
sudo yum install glew-devel freeglut-devel mesa-libGL-devel
# или для Fedora:
sudo dnf install glew-devel freeglut-devel mesa-libGL-devel
```

### Arch Linux:
```bash
sudo pacman -S glew freeglut mesa
```

## Компиляция

### Используя Makefile:
```bash
make
```

### Используя CMake:
```bash
mkdir build
cd build
cmake ..
make
```

## Запуск

### Быстрый запуск (рекомендуется):
```bash
./run.sh
```

### После компиляции с Makefile:
```bash
./pvo_app
```

### После компиляции с CMake:
```bash
cd build
./pvo_app
```

## Структура проекта

- `src/main.cpp` - основной файл приложения
- `src/shaders/vertex.glsl` - вершинный шейдер
- `src/shaders/fragment.glsl` - фрагментный шейдер
- `CMakeLists.txt` - файл конфигурации CMake
- `Makefile` - файл для компиляции с make

## Особенности

- 3D пространство с плоской поверхностью (земля)
- Персонажная камера с управлением WASD и мышью
- 5 тестовых кубов в разных позициях
- Цветная отрисовка без шейдеров (совместимость с Wayland)
- Современный OpenGL (compatibility profile)
- Поддержка Wayland и X11

## Решение проблемы с Wayland

Если у вас экран остается зеленым и камера не двигается, это означает, что вы используете Wayland вместо X11. 
Проблема решена путем перехода на простую отрисовку без шейдеров.

### Для запуска:
```bash
./wayland_final_test.sh
```

## 3D Пространство и камера

Приложение создает полноценное 3D пространство с:
- Большой плоской поверхностью (земля) размером 20x20 единиц
- Свободно управляемой камерой от первого лица
- Реалистичным освещением с источником света
- Плавным движением и поворотами

### Управление:
- **WASD** - движение
- **Пробел/C** - подъем/спуск
- **Мышь** - поворот камеры
- **ESC** - выход

Подробные инструкции по управлению см. в файле `CONTROLS.md`

## Возможные проблемы

1. **Ошибка "GL/glew.h: No such file or directory"**
   - Установите библиотеку GLEW: `sudo apt-get install libglew-dev`

2. **Ошибка "GL/glut.h: No such file or directory"**
   - Установите библиотеку GLUT: `sudo apt-get install freeglut3-dev`

3. **Ошибка "cannot find -lGL"**
   - Установите OpenGL библиотеки: `sudo apt-get install libgl1-mesa-dev`

4. **Ошибка при запуске "X11 connection failed"**
   - Убедитесь, что у вас запущен X сервер или используйте виртуальный дисплей 
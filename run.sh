#!/bin/bash

# Создаем директорию для сборки, если ее нет
if [ ! -d "build" ]; then
    mkdir build
fi

# Переходим в директорию сборки
cd build

echo "Компиляция проекта..."
cmake .. && make

if [ $? -eq 0 ]; then
    echo "Компиляция успешна! Запуск приложения..."
    echo "Для выхода нажмите Ctrl+C"
    ./pvo_app
else
    echo "Ошибка компиляции с помощью CMake!"
    exit 1
fi 
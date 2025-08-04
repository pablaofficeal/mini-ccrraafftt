cmake_minimum_required(VERSION 3.10)
project(PVO_OpenGL_Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим необходимые пакеты
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

# Добавляем исполняемый файл
add_executable(pvo_app
    src/main.cpp
    src/camera.cpp
    src/input.cpp
    src/renderer.cpp
    src/shader.cpp
    src/world.cpp
    src/PerlinNoise.cpp
)

# Подключаем заголовочные файлы
target_include_directories(pvo_app PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Подключаем библиотеки
target_link_libraries(pvo_app
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
)

# Копируем шейдеры в директорию сборки
file(COPY src/shaders DESTINATION ${CMAKE_BINARY_DIR}/src)
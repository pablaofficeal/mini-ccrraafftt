#version 330 core

layout(location = 0) in vec3 aPos;      // позиция вершины
layout(location = 1) in vec3 aNormal;   // нормаль вершины
layout(location = 2) in vec2 aTexCoord; // текстурные координаты

// Uniform матрицы для трансформаций
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;      // позиция фрагмента в мировом пространстве
out vec3 Normal;       // нормаль в мировом пространстве
out vec2 TexCoord;     // текстурные координаты

void main()
{
    // Вычисляем позицию фрагмента в мировом пространстве
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Трансформируем нормаль в мировое пространство
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Передаем текстурные координаты
    TexCoord = aTexCoord;
    
    // Вычисляем позицию в пространстве отсечения
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
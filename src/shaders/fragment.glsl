#version 330 core

in vec3 FragPos;      // позиция фрагмента в мировом пространстве
in vec3 Normal;       // нормаль в мировом пространстве
in vec2 TexCoord;     // текстурные координаты

out vec4 FragColor;   // цвет фрагмента

// Материал объекта
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Источник света
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;     // позиция камеры

void main()
{
    // Нормализуем нормаль
    vec3 norm = normalize(Normal);
    
    // Направление к источнику света
    vec3 lightDir = normalize(light.position - FragPos);
    
    // Направление к камере
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Отраженное направление
    vec3 reflectDir = reflect(-lightDir, norm);
    
    // Ambient компонент
    vec3 ambient = light.ambient * material.ambient;
    
    // Diffuse компонент
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Specular компонент
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    // Финальный цвет
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 
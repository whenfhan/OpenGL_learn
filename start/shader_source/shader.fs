#version 330 core

out vec4 FragColor;

struct Material{
    sampler2D   diffuse;
    sampler2D   specular;      // 镜面光照
    float       shininess;     // 反光度
};

// 定向光源
struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 点光源
struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    // 距离衰减参数
    float constant;
    float linear;
    float quadratic;
};

// 聚光源
struct SpotLight{
    // 聚光参数
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    // 光照参数
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    // 距离衰减参数
    float constant;
    float linear;
    float quadratic;
};

#define NR_POINTLIGHTS 4


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINTLIGHTS];
uniform SpotLight spotLight;


vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 定向光源
    vec3 result = calcDirLight(dirLight, norm, viewDir);

    // 点光源
    for(int i = 0; i < NR_POINTLIGHTS; ++i)
        result += calcPointLight(pointLights[i], norm, FragPos,viewDir);

    // 聚光源
    result += calcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}


vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    float diff = max(dot(lightDir, normal), 0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    float diff = max(dot(lightDir, normal), 0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 距离衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射
    float diff = max(dot(lightDir, normal), 0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 距离衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // 聚光衰减
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    return (ambient + diffuse + specular) * attenuation * intensity;
}
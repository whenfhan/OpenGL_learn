#version 330 core

struct Material{
    sampler2D   diffuse;
    sampler2D   specular;      // 镜面光照
    float       shininess;     // 反光度
};

struct Light{
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction)); 

    if(theta > light.cutOff){
        // 距离衰减强度
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

        // 漫反射
        vec3 norm = normalize(Normal);
        float diff = max(dot(lightDir, norm), 0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

        // 镜面光
        vec3 viewDir = normalize(viewPos - FragPos); // 观察方向
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

        vec3 result = ambient + (diffuse + specular) * attenuation;
        FragColor = vec4(result, 1.0);
    }
    else{
        FragColor = vec4(ambient, 1.0f);
    }
}
#version 330 core

out vec4 FragColor;


struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//Material
in vec3 Ka;
in vec3 Kd;
in vec3 Ks;

in vec3 Normal;
in vec3 FragPos;

uniform Light light;

uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;

void main()
{    
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);

    //ambient
    vec3 ambient = Ka * light.ambient * objectColor;

    //specular
    float specularIntensity = pow(max(dot(reflectVec,cameraVec), 0), light.shininess);
    vec3 specular = Ks * light.specular * specularIntensity * lightColor;

    //diffuse
    vec3 diffuse = Kd * light.diffuse * max(dot(lightDir,Normal), 0) * objectColor;

    
   FragColor = vec4((ambient + diffuse + specular) * objectColor ,1.0f);
}
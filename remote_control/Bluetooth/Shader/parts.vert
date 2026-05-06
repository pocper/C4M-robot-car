#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

struct Texture
{
    vec3 a_Ka;
    vec3 a_Kd;
    vec3 a_Ks;
};

out vec3 Normal;
out vec3 FragPos;

out vec3 Ka;
out vec3 Kd;
out vec3 Ks;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform Texture texture;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(modelMat))) * aNormal;
    FragPos =  vec3(modelMat * vec4(aPos, 1.0f));

    Ka = texture.a_Ka;
	Kd = texture.a_Kd;
	Ks = texture.a_Ks;
}
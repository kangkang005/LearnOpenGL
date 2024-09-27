#version 330 core
layout (location = 0) in vec3 aPos;
// 向每个顶点添加了一个法向量并更新了顶点着色器
layout (location = 1) in vec3 aNormal;     //传入法线向量

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);   //对传入的顶点数据 进行世界空间矩阵转换
}
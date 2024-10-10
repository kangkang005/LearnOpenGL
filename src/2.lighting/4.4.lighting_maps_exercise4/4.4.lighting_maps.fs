#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    sampler2D emission;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float matrixlight;
uniform float matrixmove;

vec3 emission;
float x = TexCoords.x;
float y = TexCoords.y;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
      // emission
    // vec3 emission = texture(material.emission, TexCoords).rgb;
    // 随时间变化的浮点数光强和纹理坐标位移，光带就能既变化又流动
    // vec3 emission = matrixlight*texture(material.emission,vec2(TexCoords.x,TexCoords.y+matrixmove)).rgb;
    // vec3 emission = texture(material.emission, TexCoords * vec2(0.7) + vec2(0.1)).rgb;
    // * vec(0.8)，裁剪边框 0.1，+ vec2(0.1)，起始坐标为 0.1

    // TODO: 如何裁剪纹理的边框
    vec2 TexCoordsTemp = TexCoords * vec2(0.8) + vec2(0.1);
    if (x < 0.1 || x > 0.9 || y < 0.1 || y > 0.9) {
		emission = vec3(0.0);
	} else {
		emission = matrixlight * texture(material.emission, TexCoordsTemp + vec2(0.0, matrixmove)).rgb;
	}
        
    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 
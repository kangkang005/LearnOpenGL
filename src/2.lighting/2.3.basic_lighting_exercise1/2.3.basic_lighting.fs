#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;   //摄像机位置  观察方向
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular 镜面光照
    // 我们定义一个镜面强度 (Specular Intensity) 变量，给镜面高光一个中等亮度颜色，让它不要产生过度的影响。
    float specularStrength = 0.5;   //镜面高光强度
    vec3 viewDir = normalize(viewPos - FragPos);    // 摄像机方向
    // 需要注意的是我们对 lightDir 向量进行了取反。reflect 函数要求第一个向量是从光源指向片段位置的向量，
    // 但是 lightDir 当前正好相反，是从片段指向光源（由先前我们计算 lightDir 向量时，减法的顺序决定）。
    // 为了保证我们得到正确的 reflect 向量，我们通过对 lightDir 向量取反来获得相反的方向。
    // 第二个参数要求是一个法向量，所以我们提供的是已标准化的 norm 向量。
    vec3 reflectDir = reflect(-lightDir, norm);  //反射向量方向
    // 我们先计算视线方向与反射方向的点乘（并确保它不是负值），然后取它的 32 次幂。
    // 这个 32 是高光的反光度 (Shininess)。一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小。
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   //求夹角 算镜面高光权重
    vec3 specular = specularStrength * spec * lightColor;   //强度*权重*颜色
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 
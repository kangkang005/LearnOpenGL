#version 330 core
out vec4 FragColor;

// 所有光照的计算都是在片段着色器里进行，所以我们需要将法向量由顶点着色器传递到片段着色器。
in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient 环境光照
    //环境光照在场景里的表现非常简单，用光的颜色乘以一个很小的常量环境因子
    float ambientStrength = 0.1;        //强度
    vec3 ambient = ambientStrength * lightColor;    //强度*颜色
  	
    // 光的方向向量是光源位置向量与片段位置向量之间的向量差
    // diffuse 漫反射光照
    vec3 norm = normalize(Normal);      //归一化法线向量
    vec3 lightDir = normalize(lightPos - FragPos);  //归一化 灯光方向
    // 我们对 norm 和 lightDir 向量进行点乘，计算光源对当前片段实际的漫反射影响。结果值再乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小
    // 如果两个向量之间的角度大于 90 度，点乘的结果就会变成负数，这样会导致漫反射分量变为负数。
    // 为此，我们使用 max 函数返回两个参数之间较大的参数，从而保证漫反射分量不会变成负数。负数颜色的光照是没有定义的，所以最好避免它
    float diff = max(dot(norm, lightDir), 0.0);   //求夹角
    vec3 diffuse = diff * lightColor;   //乘以灯光颜色
            
    // 现在我们有了环境光分量和漫反射分量，我们把它们相加，然后把结果乘以物体的颜色，来获得片段最后的输出颜色。
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
} 
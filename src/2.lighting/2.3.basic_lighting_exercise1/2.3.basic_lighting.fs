#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;   //�����λ��  �۲췽��
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
    
    // specular �������
    // ���Ƕ���һ������ǿ�� (Specular Intensity) ������������߹�һ���е�������ɫ��������Ҫ�������ȵ�Ӱ�졣
    float specularStrength = 0.5;   //����߹�ǿ��
    vec3 viewDir = normalize(viewPos - FragPos);    // ���������
    // ��Ҫע��������Ƕ� lightDir ����������ȡ����reflect ����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�������
    // ���� lightDir ��ǰ�����෴���Ǵ�Ƭ��ָ���Դ������ǰ���Ǽ��� lightDir ����ʱ��������˳���������
    // Ϊ�˱�֤���ǵõ���ȷ�� reflect ����������ͨ���� lightDir ����ȡ��������෴�ķ���
    // �ڶ�������Ҫ����һ�������������������ṩ�����ѱ�׼���� norm ������
    vec3 reflectDir = reflect(-lightDir, norm);  //������������
    // �����ȼ������߷����뷴�䷽��ĵ�ˣ���ȷ�������Ǹ�ֵ����Ȼ��ȡ���� 32 ���ݡ�
    // ��� 32 �Ǹ߹�ķ���� (Shininess)��һ������ķ����Խ�ߣ�����������Խǿ��ɢ���Խ�٣��߹��ͻ�ԽС��
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   //��н� �㾵��߹�Ȩ��
    vec3 specular = specularStrength * spec * lightColor;   //ǿ��*Ȩ��*��ɫ
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 
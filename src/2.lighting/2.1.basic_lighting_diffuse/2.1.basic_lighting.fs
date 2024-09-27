#version 330 core
out vec4 FragColor;

// ���й��յļ��㶼����Ƭ����ɫ������У�����������Ҫ���������ɶ�����ɫ�����ݵ�Ƭ����ɫ����
in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient ��������
    //���������ڳ�����ı��ַǳ��򵥣��ù����ɫ����һ����С�ĳ�����������
    float ambientStrength = 0.1;        //ǿ��
    vec3 ambient = ambientStrength * lightColor;    //ǿ��*��ɫ
  	
    // ��ķ��������ǹ�Դλ��������Ƭ��λ������֮���������
    // diffuse ���������
    vec3 norm = normalize(Normal);      //��һ����������
    vec3 lightDir = normalize(lightPos - FragPos);  //��һ�� �ƹⷽ��
    // ���Ƕ� norm �� lightDir �������е�ˣ������Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ�졣���ֵ�ٳ��Թ����ɫ���õ��������������������֮��ĽǶ�Խ������������ͻ�ԽС
    // �����������֮��ĽǶȴ��� 90 �ȣ���˵Ľ���ͻ��ɸ����������ᵼ�������������Ϊ������
    // Ϊ�ˣ�����ʹ�� max ����������������֮��ϴ�Ĳ������Ӷ���֤��������������ɸ�����������ɫ�Ĺ�����û�ж���ģ�������ñ�����
    float diff = max(dot(norm, lightDir), 0.0);   //��н�
    vec3 diffuse = diff * lightColor;   //���Եƹ���ɫ
            
    // �����������˻������������������������ǰ�������ӣ�Ȼ��ѽ�������������ɫ�������Ƭ�����������ɫ��
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
} 
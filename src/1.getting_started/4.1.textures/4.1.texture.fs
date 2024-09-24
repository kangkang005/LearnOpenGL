#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

// Ƭ����ɫ��ҲӦ���ܷ���������󣬵������������ܰ�������󴫸�Ƭ����ɫ���أ�
// GLSL ��һ�����������ʹ�õ��ڽ��������ͣ����������� (Sampler)����������������Ϊ��׺��
// ���� sampler1D��sampler3D���������ǵ������е� sampler2D��
void main()
{
	// ����ʹ�� GLSL �ڽ��� texture �����������������ɫ������һ��������������������ڶ��������Ƕ�Ӧ���������ꡣ
	// texture ������ʹ��֮ǰ���õ������������Ӧ����ɫֵ���в��������Ƭ����ɫ���������������ģ���ֵ�����������ϵ� (���˺��) ��ɫ��
	FragColor = texture(texture1, TexCoord);
}
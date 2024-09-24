#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

// 片段着色器也应该能访问纹理对象，但是我们怎样能把纹理对象传给片段着色器呢？
// GLSL 有一个供纹理对象使用的内建数据类型，叫做采样器 (Sampler)，它以纹理类型作为后缀，
// 比如 sampler1D、sampler3D，或在我们的例子中的 sampler2D。
void main()
{
	// 我们使用 GLSL 内建的 texture 函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
	// texture 函数会使用之前设置的纹理参数对相应的颜色值进行采样。这个片段着色器的输出就是纹理的（插值）纹理坐标上的 (过滤后的) 颜色。
	FragColor = texture(texture1, TexCoord);
}
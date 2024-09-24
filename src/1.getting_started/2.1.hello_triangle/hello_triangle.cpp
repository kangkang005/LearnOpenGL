#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*
	OpenGL 3.3 �Լ��͸��߰汾�У�GLSL �汾�ź� OpenGL �İ汾��ƥ��ģ�����˵ GLSL 420 �汾��Ӧ�� OpenGL 4.2��������ͬ����ȷ��ʾ���ǻ�ʹ�ú���ģʽ��

	��һ����ʹ�� in �ؼ��֣��ڶ�����ɫ�����������е����붥������(Input Vertex Attribute)����������ֻ����λ��(Position) ���ݣ���������ֻ��Ҫһ���������ԡ�
	GLSL ��һ�������������ͣ������� 1 �� 4 �� float �������������������Դ����ĺ�׺���ֿ�����������ÿ�����㶼��һ�� 3D ���꣬���Ǿʹ���һ�� vec3 ������� aPos��
	����ͬ��Ҳͨ�� layout(location = 0) �趨�����������λ��ֵ(Location) ��
*/
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
/*
    Ƭ����ɫ�� (Fragment Shader) �ǵڶ���Ҳ�����һ�����Ǵ��㴴����������Ⱦ�����ε���ɫ����Ƭ����ɫ���������Ǽ�������������ɫ�����

    Ƭ����ɫ��ֻ��Ҫһ��������������������һ�� 4 ��������������ʾ�������յ������ɫ������Ӧ���Լ�������������
    ���������������ʹ�� out �ؼ��֣�������������Ϊ FragColor�����棬���ǽ�һ�� Alpha ֵΪ 1.0 (1.0 ������ȫ��͸��) ���ٻ�ɫ�� vec4 ��ֵ����ɫ�����
*/
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    // ������ɫ��������Ҫ��������ɫ�������Բ�����ʽ�ṩ�� glCreateShader�������������ڴ���һ��������ɫ�������ݵĲ����� GL_VERTEX_SHADER
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // �������ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    /*  
        ����ڵ��� glCompileShader ������Ƿ�ɹ� :
			�������Ƕ���һ�����ͱ�������ʾ�Ƿ�ɹ����룬��������һ�����������Ϣ������еĻ�����������
			Ȼ�������� glGetShaderiv ����Ƿ����ɹ����������ʧ�ܣ����ǻ��� glGetShaderInfoLog ��ȡ������Ϣ��Ȼ���ӡ����
    */
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ����Ƭ����ɫ���Ĺ����붥����ɫ�����ƣ�ֻ��������ʹ�� GL_FRAGMENT_SHADER ������Ϊ��ɫ������
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /*
		��ɫ��������� (Shader Program Object) �Ƕ����ɫ���ϲ�֮������������ɵİ汾��
        ���Ҫʹ�øղű������ɫ�����Ǳ������������ (Link) Ϊһ����ɫ���������Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
        �Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ�á�

	    ��������ɫ����һ�������ʱ�������ÿ����ɫ����������ӵ��¸���ɫ�������롣����������벻ƥ���ʱ�����õ�һ�����Ӵ���
    */
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    // ��������Ҫ��֮ǰ�������ɫ�����ӵ���������ϣ�Ȼ���� glLinkProgram ��������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    // ���㻺����� (Vertex Buffer Objects, VBO)
    /*
        ͨ�����㻺����� (Vertex Buffer Objects, VBO) ��������ڴ棬������ GPU �ڴ棨ͨ������Ϊ�Դ棩�д���������㡣
        ʹ����Щ�������ĺô������ǿ���һ���Եķ���һ�������ݵ��Կ��ϣ�������ÿ�����㷢��һ�Ρ�
        �� CPU �����ݷ��͵��Կ���Խ���������ֻҪ�������Ƕ�Ҫ���Ծ���һ���Է��;����ܶ�����ݡ�
        �����ݷ������Կ����ڴ��к󣬶�����ɫ���������������ʶ��㣬���Ǹ��ǳ���Ĺ��̡�
    */
    // ����������� (Vertex Array Object, VAO) 
    /*
        ����������� (Vertex Array Object, VAO) �����񶥵㻺������������󶨣��κ����Ķ������Ե��ö��ᴢ������� VAO �С�
        �����ĺô����ǣ������ö�������ָ��ʱ����ֻ��Ҫ����Щ����ִ��һ�Σ�֮���ٻ��������ʱ��ֻ��Ҫ����Ӧ�� VAO �����ˡ�
        ��ʹ�ڲ�ͬ�������ݺ���������֮���л���÷ǳ��򵥣�ֻ��Ҫ�󶨲�ͬ�� VAO �����ˡ�
    */
    unsigned int VBO, VAO;
    // ����һ�� VAO �ʹ���һ�� VBO ������
    glGenVertexArrays(1, &VAO);
    // ʹ�� glGenBuffers ��������һ�����л��� ID �� VBO ����
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // ��VAO
    glBindVertexArray(VAO);

    // 0. ���ƶ������鵽�����й�OpenGLʹ��
    // ʹ�� glBindBuffer �������´����� VBO ����󶨵� GL_ARRAY_BUFFER Ŀ����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
    glBufferData ��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ��������ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵� GL_ARRAY_BUFFER Ŀ���ϡ��ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵� sizeof ������������ݴ�С���С�����������������ϣ�����͵�ʵ�����ݡ�

        ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��

        1. GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
        2. GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
        3. GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
        �����ε�λ�����ݲ���ı䣬ÿ����Ⱦ����ʱ������ԭ������������ʹ����������� GL_STATIC_DRAW�����������˵һ�������е����ݽ�Ƶ�����ı䣬��ôʹ�õ����;��� GL_DYNAMIC_DRAW �� GL_STREAM_DRAW����������ȷ���Կ������ݷ����ܹ�����д����ڴ沿�֡�

        ���������Ѿ��Ѷ������ݴ������Կ����ڴ��У��� VBO ������㻺��������
    */
    // 1. ���ö�������ָ��
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
        glVertexAttribPointer �����Ĳ����ǳ��࣬�����һ���һ�������ǣ�
			1. ��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ�� layout(location = 0) ������ position �������Ե�λ��ֵ (Location) �������԰Ѷ������Ե�λ��ֵ����Ϊ 0��
                ��Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ��� 0��
			2. �ڶ�������ָ���������ԵĴ�С������������һ�� vec3������ 3 ��ֵ��ɣ����Դ�С�� 3��
			3. ����������ָ�����ݵ����ͣ������� GL_FLOAT(GLSL �� vec* �����ɸ�����ֵ��ɵ�)��
			4. �¸��������������Ƿ�ϣ�����ݱ���׼�� (Normalize)�������������Ϊ GL_TRUE���������ݶ��ᱻӳ�䵽 0�������з����� signed ������ - 1���� 1 ֮�䡣���ǰ�������Ϊ GL_FALSE��
			5. ����������������� (Stride)�������������������Ķ���������֮��ļ���������¸���λ�������� 3 �� float ֮�����ǰѲ�������Ϊ 3 * sizeof(float)��
                Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ 0 ���� OpenGL �������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���
                һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע�������������˼��˵���Ǵ�������Եڶ��γ��ֵĵط����������� 0 λ��֮���ж����ֽڣ���
			6. ���һ�������������� void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ���� (Offset)������λ������������Ŀ�ͷ������������ 0�����ǻ��ں�����ϸ�������������
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // ���������Ѿ������� OpenGL ����ν��Ͷ������ݣ���������Ӧ��ʹ�� glEnableVertexAttribArray���Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // һ�㵱�������ƶ������ʱ��������Ҫ���� / �������е� VAO���ͱ���� VBO ������ָ��)��Ȼ�󴢴����ǹ�����ʹ�á�
    // �����Ǵ�����������ʱ����ó���Ӧ�� VAO��������������������ٽ�� VAO��
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 2. ��������Ⱦһ������ʱҪʹ����ɫ������
        // draw our first triangle
        glUseProgram(shaderProgram);
        // 3. ��������
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays ������һ�����������Ǵ�����Ƶ� OpenGL ͼԪ�����͡�
        // ����������һ��ʼʱ˵��������ϣ�����Ƶ���һ�������Σ����ﴫ�� GL_TRIANGLES ������
        // �ڶ�������ָ���˶����������ʼ���������������� 0�����һ������ָ�����Ǵ�����ƶ��ٸ����㣬
        // ������ 3������ֻ�����ǵ���������Ⱦһ�������Σ���ֻ�� 3 �����㳤����
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
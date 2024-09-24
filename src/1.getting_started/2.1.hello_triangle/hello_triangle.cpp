#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*
	OpenGL 3.3 以及和更高版本中，GLSL 版本号和 OpenGL 的版本是匹配的（比如说 GLSL 420 版本对应于 OpenGL 4.2）。我们同样明确表示我们会使用核心模式。

	下一步，使用 in 关键字，在顶点着色器中声明所有的输入顶点属性(Input Vertex Attribute)。现在我们只关心位置(Position) 数据，所以我们只需要一个顶点属性。
	GLSL 有一个向量数据类型，它包含 1 到 4 个 float 分量，包含的数量可以从它的后缀数字看出来。由于每个顶点都有一个 3D 坐标，我们就创建一个 vec3 输入变量 aPos。
	我们同样也通过 layout(location = 0) 设定了输入变量的位置值(Location) 。
*/
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
/*
    片段着色器 (Fragment Shader) 是第二个也是最后一个我们打算创建的用于渲染三角形的着色器。片段着色器所做的是计算像素最后的颜色输出。

    片段着色器只需要一个输出变量，这个变量是一个 4 分量向量，它表示的是最终的输出颜色，我们应该自己将其计算出来。
    声明输出变量可以使用 out 关键字，这里我们命名为 FragColor。下面，我们将一个 Alpha 值为 1.0 (1.0 代表完全不透明) 的橘黄色的 vec4 赋值给颜色输出。
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
    // 创建着色器：把需要创建的着色器类型以参数形式提供给 glCreateShader。由于我们正在创建一个顶点着色器，传递的参数是 GL_VERTEX_SHADER
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 把这个着色器源码附加到着色器对象上，然后编译它
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    /*  
        检测在调用 glCompileShader 后编译是否成功 :
			首先我们定义一个整型变量来表示是否成功编译，还定义了一个储存错误消息（如果有的话）的容器。
			然后我们用 glGetShaderiv 检查是否编译成功。如果编译失败，我们会用 glGetShaderInfoLog 获取错误消息，然后打印它。
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

    // 编译片段着色器的过程与顶点着色器类似，只不过我们使用 GL_FRAGMENT_SHADER 常量作为着色器类型
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
		着色器程序对象 (Shader Program Object) 是多个着色器合并之后并最终链接完成的版本。
        如果要使用刚才编译的着色器我们必须把它们链接 (Link) 为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序。
        已激活着色器程序的着色器将在我们发送渲染调用的时候被使用。

	    当链接着色器至一个程序的时候，它会把每个着色器的输出链接到下个着色器的输入。当输出和输入不匹配的时候，你会得到一个连接错误。
    */
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    // 在我们需要把之前编译的着色器附加到程序对象上，然后用 glLinkProgram 链接它们
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

    // 顶点缓冲对象 (Vertex Buffer Objects, VBO)
    /*
        通过顶点缓冲对象 (Vertex Buffer Objects, VBO) 管理这个内存，它会在 GPU 内存（通常被称为显存）中储存大量顶点。
        使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。
        从 CPU 把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据。
        当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。
    */
    // 顶点数组对象 (Vertex Array Object, VAO) 
    /*
        顶点数组对象 (Vertex Array Object, VAO) 可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个 VAO 中。
        这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的 VAO 就行了。
        这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的 VAO 就行了。
    */
    unsigned int VBO, VAO;
    // 创建一个 VAO 和创建一个 VBO 很类似
    glGenVertexArrays(1, &VAO);
    // 使用 glGenBuffers 函数生成一个带有缓冲 ID 的 VBO 对象
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // 绑定VAO
    glBindVertexArray(VAO);

    // 0. 复制顶点数组到缓冲中供OpenGL使用
    // 使用 glBindBuffer 函数把新创建的 VBO 缓冲绑定到 GL_ARRAY_BUFFER 目标上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
    glBufferData 是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到 GL_ARRAY_BUFFER 目标上。第二个参数指定传输数据的大小(以字节为单位)；用一个简单的 sizeof 计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。

        第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：

        1. GL_STATIC_DRAW ：数据不会或几乎不会改变。
        2. GL_DYNAMIC_DRAW：数据会被改变很多。
        3. GL_STREAM_DRAW ：数据每次绘制时都会改变。
        三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是 GL_STATIC_DRAW。如果，比如说一个缓冲中的数据将频繁被改变，那么使用的类型就是 GL_DYNAMIC_DRAW 或 GL_STREAM_DRAW，这样就能确保显卡把数据放在能够高速写入的内存部分。

        现在我们已经把顶点数据储存在显卡的内存中，用 VBO 这个顶点缓冲对象管理。
    */
    // 1. 设置顶点属性指针
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
        glVertexAttribPointer 函数的参数非常多，所以我会逐一介绍它们：
			1. 第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用 layout(location = 0) 定义了 position 顶点属性的位置值 (Location) 吗？它可以把顶点属性的位置值设置为 0。
                因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入 0。
			2. 第二个参数指定顶点属性的大小。顶点属性是一个 vec3，它由 3 个值组成，所以大小是 3。
			3. 第三个参数指定数据的类型，这里是 GL_FLOAT(GLSL 中 vec* 都是由浮点数值组成的)。
			4. 下个参数定义我们是否希望数据被标准化 (Normalize)。如果我们设置为 GL_TRUE，所有数据都会被映射到 0（对于有符号型 signed 数据是 - 1）到 1 之间。我们把它设置为 GL_FALSE。
			5. 第五个参数叫做步长 (Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在 3 个 float 之后，我们把步长设置为 3 * sizeof(float)。
                要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为 0 来让 OpenGL 决定具体步长是多少（只有当数值是紧密排列时才可用）。
                一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注：这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组 0 位置之间有多少字节）。
			6. 最后一个参数的类型是 void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量 (Offset)。由于位置数据在数组的开头，所以这里是 0。我们会在后面详细解释这个参数。
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 现在我们已经定义了 OpenGL 该如何解释顶点数据，我们现在应该使用 glEnableVertexAttribArray，以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // 一般当你打算绘制多个物体时，你首先要生成 / 配置所有的 VAO（和必须的 VBO 及属性指针)，然后储存它们供后面使用。
    // 当我们打算绘制物体的时候就拿出相应的 VAO，绑定它，绘制完物体后，再解绑 VAO。
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

        // 2. 当我们渲染一个物体时要使用着色器程序
        // draw our first triangle
        glUseProgram(shaderProgram);
        // 3. 绘制物体
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays 函数第一个参数是我们打算绘制的 OpenGL 图元的类型。
        // 由于我们在一开始时说过，我们希望绘制的是一个三角形，这里传递 GL_TRIANGLES 给它。
        // 第二个参数指定了顶点数组的起始索引，我们这里填 0。最后一个参数指定我们打算绘制多少个顶点，
        // 这里是 3（我们只从我们的数据中渲染一个三角形，它只有 3 个顶点长）。
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
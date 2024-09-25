#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <imgui_all.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    //设置ImGui上下文
    IMGUI_CHECKVERSION();    // 检查版本
    ImGui::CreateContext();  // 创建上下文
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //设置颜色风格
    ImGui::StyleColorsDark();

    //Setup Platform/Render bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);  //在GLFW窗口上进行初始化
    ImGui_ImplOpenGL3_Init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        //Start the Dear ImGui frame  启动ImGui Frame框架
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            //开始绘制ImGui
            ImGui::Begin("IBinary Windows");//Create a window called "Hello,world!" and append into it.
            //窗口控件逻辑放在这
            ImGui::Text("IBinary Blog");
            //ImGui::SameLine();
            ImGui::Indent();//另一起行制表符开始绘制Button
            ImGui::Button("2222", ImVec2(100, 50));

            ImGui::End();
        }

        // 在每个新的渲染迭代开始的时候我们总是希望清屏，否则我们仍能看见上一次迭代的渲染结果。
        // 我们可以通过调用 glClear 函数来清空屏幕的颜色缓冲，它接受一个缓冲位 (Buffer Bit) 来指定要清空的缓冲，
        // 可能的缓冲位有 GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT。由于现在我们只关心颜色值，所以我们只清空颜色缓冲。
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 除了 glClear 之外，我们还调用了 glClearColor 来设置清空屏幕所用的颜色。当调用 glClear 函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为 glClearColor 里所设置的颜色。
        glClear(GL_COLOR_BUFFER_BIT);

        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//必须在绘制完Open之后接着绘制Imgui

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
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
    // OpenGL 版本是 3.3 (Major.Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // 主版本号 (Major) 设为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // 次版本号 (Minor) 设为 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 告诉 GLFW 使用的是核心模式 (Core-profile)

    // 如果使用的是 Mac OS X 系统，你还需要加下面这行代码到你的初始化代码中这些配置才能起作用
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
    glfwMakeContextCurrent(window);     // 通知 GLFW 将当前窗口的上下文设置为当前线程的主上下文
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // 当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数 (Callback Function)，它会在每次窗口大小被调整的时候被调用。

    // glad: 是用来管理 OpenGL 的函数指针的
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
    // glfwWindowShouldClose 函数在我们每次循环的开始前检查一次 GLFW 是否被要求退出，如果是的话，该函数返回 true，渲染循环将停止运行，之后我们就可以关闭应用程序。
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

        //Show another simple window

        glClear(GL_COLOR_BUFFER_BIT);

        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//必须在绘制完Open之后接着绘制Imgui

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        // glfwSwapBuffers 函数会交换颜色缓冲（它是一个储存着 GLFW 窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwSwapBuffers(window);
        // glfwPollEvents 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
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
    // glfwGetKey 函数: 将一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // 如果用户的确按下了返回键，我们将通过使用 glfwSetwindowShouldClose 把 WindowShouldClose 属性设置为 true 来关闭 GLFW
        glfwSetWindowShouldClose(window, true);
}

// 告诉 OpenGL 渲染窗口的尺寸大小
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport 函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    // 我们实际上也可以将视口的维度设置为比 GLFW 的维度小，这样子之后所有的 OpenGL 渲染将会在一个更小的窗口中显示，这样子的话我们也可以将一些其它元素显示在 OpenGL 视口之外
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

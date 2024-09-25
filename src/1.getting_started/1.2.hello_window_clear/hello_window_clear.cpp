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

    //����ImGui������
    IMGUI_CHECKVERSION();    // ���汾
    ImGui::CreateContext();  // ����������
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //������ɫ���
    ImGui::StyleColorsDark();

    //Setup Platform/Render bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);  //��GLFW�����Ͻ��г�ʼ��
    ImGui_ImplOpenGL3_Init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        //Start the Dear ImGui frame  ����ImGui Frame���
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            //��ʼ����ImGui
            ImGui::Begin("IBinary Windows");//Create a window called "Hello,world!" and append into it.
            //���ڿؼ��߼�������
            ImGui::Text("IBinary Blog");
            //ImGui::SameLine();
            ImGui::Indent();//��һ�����Ʊ����ʼ����Button
            ImGui::Button("2222", ImVec2(100, 50));

            ImGui::End();
        }

        // ��ÿ���µ���Ⱦ������ʼ��ʱ����������ϣ�������������������ܿ�����һ�ε�������Ⱦ�����
        // ���ǿ���ͨ������ glClear �����������Ļ����ɫ���壬������һ������λ (Buffer Bit) ��ָ��Ҫ��յĻ��壬
        // ���ܵĻ���λ�� GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT �� GL_STENCIL_BUFFER_BIT��������������ֻ������ɫֵ����������ֻ�����ɫ���塣
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // ���� glClear ֮�⣬���ǻ������� glClearColor �����������Ļ���õ���ɫ�������� glClear �����������ɫ����֮��������ɫ���嶼�ᱻ���Ϊ glClearColor �������õ���ɫ��
        glClear(GL_COLOR_BUFFER_BIT);

        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//�����ڻ�����Open֮����Ż���Imgui

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
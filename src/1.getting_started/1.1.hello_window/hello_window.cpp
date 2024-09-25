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
    // OpenGL �汾�� 3.3 (Major.Minor)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // ���汾�� (Major) ��Ϊ 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // �ΰ汾�� (Minor) ��Ϊ 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ���� GLFW ʹ�õ��Ǻ���ģʽ (Core-profile)

    // ���ʹ�õ��� Mac OS X ϵͳ���㻹��Ҫ���������д��뵽��ĳ�ʼ����������Щ���ò���������
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
    glfwMakeContextCurrent(window);     // ֪ͨ GLFW ����ǰ���ڵ�����������Ϊ��ǰ�̵߳���������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����������ǿ��ԶԴ���ע��һ���ص����� (Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�

    // glad: ���������� OpenGL �ĺ���ָ���
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
    // glfwWindowShouldClose ����������ÿ��ѭ���Ŀ�ʼǰ���һ�� GLFW �Ƿ�Ҫ���˳�������ǵĻ����ú������� true����Ⱦѭ����ֹͣ���У�֮�����ǾͿ��Թر�Ӧ�ó���
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

        //Show another simple window

        glClear(GL_COLOR_BUFFER_BIT);

        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//�����ڻ�����Open֮����Ż���Imgui

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        // glfwSwapBuffers �����ύ����ɫ���壨����һ�������� GLFW ����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwSwapBuffers(window);
        // glfwPollEvents ���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
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
    // glfwGetKey ����: ��һ�������Լ�һ��������Ϊ���롣����������᷵����������Ƿ����ڱ�����
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // ����û���ȷ�����˷��ؼ������ǽ�ͨ��ʹ�� glfwSetwindowShouldClose �� WindowShouldClose ��������Ϊ true ���ر� GLFW
        glfwSetWindowShouldClose(window, true);
}

// ���� OpenGL ��Ⱦ���ڵĳߴ��С
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport ����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
    // ����ʵ����Ҳ���Խ��ӿڵ�ά������Ϊ�� GLFW ��ά��С��������֮�����е� OpenGL ��Ⱦ������һ����С�Ĵ�������ʾ�������ӵĻ�����Ҳ���Խ�һЩ����Ԫ����ʾ�� OpenGL �ӿ�֮��
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

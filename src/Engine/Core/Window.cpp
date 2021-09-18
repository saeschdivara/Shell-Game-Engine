#include "Engine/Core/Window.h"
#include "Engine/Core/Logger.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Core/Events/KeyEvent.h"
#include "Engine/Core/Events/MouseEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

namespace Shell {
    void Window::Init() {
        /* Initialize the library */
        if (!glfwInit()) {
            SHELL_CORE_ERROR("GLFW could not be initialised");
            return;
        }

#ifdef __APPLE__
        /* We need to explicitly ask for a 3.2 context on OS X */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
        if (!m_Window) {
            SHELL_CORE_ERROR("Window could not be initialised");
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    }

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
             0.5f, -0.5f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };
    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data2[] = {
            -.5f, -.5f, 0.5f,
            1.0f, -1.0f, 0.5f,
            0.0f, 1.0f, 0.5f,
    };
    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

        // Create the Shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if(VertexShaderStream.is_open()){
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
            getchar();
            return 0;
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if(FragmentShaderStream.is_open()){
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Compile Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }

        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }

        // Link the program
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }

        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
    }

    void Window::Render() {
        SHELL_CORE_INFO(glGetString(GL_VERSION));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        GLuint programID = LoadShaders(
                "../../Shaders/SimpleVertexShader.vert",
                "../../Shaders/SimpleFragmentShader.frag"
        );

        // This will identify our vertex buffer
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        Renderer::Instance().get()->AddBatch({
             .vertexbuffer = vertexbuffer,
             .programID =  programID,
         });

        // This will identify our vertex buffer
        GLuint vertexbuffer2;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer2);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);

        Renderer::Instance().get()->AddBatch({
            .vertexbuffer = vertexbuffer2,
            .programID =  programID,
        });

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(m_Window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

            // execute update handler / engine code
            OnUpdate();

            /* Swap front and back buffers */
            glfwSwapBuffers(m_Window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }

    void Window::OnUpdate() {
        Renderer::Instance().get()->RenderBatch();
    }

    void Window::SetupCallbacks(const Window::EventCallbackFn &callback) {
        m_Data.Callback = callback;

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetKeyCallback(m_Window, [](GLFWwindow * window, int key, int scancode, int action, int mods) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS) {
                KeyPressedEvent event(key, 0);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_RELEASE) {
                KeyReleasedEvent event(key);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_REPEAT) {
                KeyPressedEvent event(key, 1);
                dataPointer->Callback(event);
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window,  int button, int action, int mods) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            if (action == GLFW_PRESS) {
                MouseButtonPressedEvent event(button);
                dataPointer->Callback(event);
            }
            else if (action == GLFW_RELEASE) {
                MouseButtonReleasedEvent event(button);
                dataPointer->Callback(event);
            }

        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(xOffset, yOffset);
            dataPointer->Callback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            auto dataPointer = static_cast<Window::WindowData *>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event((float) xPos, (float)yPos);
            dataPointer->Callback(event);
        });
    }
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace myOpenGL{
    void Render(){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    int myMain(){
        SPDLOG_INFO(" myOpenGL start "); 
        if(!glfwInit()){
            const char* errorlog =nullptr; 
            glfwGetError(&errorlog); 
            SPDLOG_ERROR(" glfw init faile : {}", errorlog); 
            return -1; 
        }
        
        SPDLOG_INFO(" GLFW OpenGL core profile  "); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto window = glfwCreateWindow(640, 480, "hello my openGL TEST ", NULL, NULL); 
        if(!window){
            SPDLOG_ERROR( "failed to create glfwWindow "); 
            glfwTerminate(); 
            return -1; 
        }
        glfwMakeContextCurrent(window); 
        
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            SPDLOG_ERROR( "failed to initial  glad "); 
            glfwTerminate(); 
            return -1; 
        }
        //리턴값 GLubyte*를 형변환해서 출력 해야.  (void*)로 캐스팅하면 포인터 주소값 출력. 
        auto openglVersion = glGetString(GL_VERSION); 
        SPDLOG_INFO("glversion :{}", reinterpret_cast<const char*>(openglVersion) ); 

        SPDLOG_INFO("Main loop start "); 
        if(!glfwWindowShouldClose(window)){
            Render(); 
            glfwSwapBuffers(window); 
            glfwPollEvents(); 
        }

        glfwTerminate(); 
        return 0;
    }
}
#include "controller.h"

std::unique_ptr<Controller> Controller::CreateController(const std::string& title, const int width, const int height)
{
    auto controller = std::unique_ptr<Controller> (new Controller()); 
    if(controller){
        controller->Init(title, width, height); 
    }
    return std::move(controller);
}

int Controller::Init(const std::string &title, const int width, const int height)
{
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

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); 
    if(!m_window){
        SPDLOG_ERROR( "failed to create glfwWindow "); 
        glfwTerminate(); 
        return -1; 
    }

    //원도우를 만들먼 컨텍스트가 만들어 진다. 그  직후 바로 원도를 컨텍스트에 등록해야. 
    glfwMakeContextCurrent(m_window); 

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        SPDLOG_ERROR( "failed to initial  glad "); 
        glfwTerminate(); 
        return -1; 
    }

    //리턴값 GLubyte*를 형변환해서 출력 해야.  (void*)로 캐스팅하면 포인터 주소값 출력. 
    auto openglVersion = glGetString(GL_VERSION); 
    SPDLOG_INFO("glversion :{}", reinterpret_cast<const char*>(openglVersion) ); 

    return 1; 
}

void Controller::Run()
{
    
    SPDLOG_INFO("Main loop start {}", (void*)m_window); 
    while(!glfwWindowShouldClose(m_window)){
        Render(); 
        glfwSwapBuffers(m_window); 
        glfwPollEvents(); 
    }

}

void Controller::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Controller::Get()
{
}

Controller::~Controller()
{
    glfwTerminate(); 
}

#include "controller.h"


float vertices[6] = { //삼각형 좌표 정보. 
    -0.5f, -0.5f,
    0.0f,  0.5f,
    0.5f, -0.5f,
};

//callback함수. --화면의 사이즈가 변경되면 이벤트가 발생하고 이 함수로 들어온다. 
void frambufferSize_Callback(GLFWwindow *window, int width, int height)
{
    SPDLOG_INFO(" Frame buffer change, {} , {}", width, height); 
    glViewport(0, 0, width, height); 
}

void keyevent_Callback(GLFWwindow*window, int key, int code, int action, int mode){
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        SPDLOG_INFO(" key {}, scan {}, action {}", key, code, 
            action == GLFW_PRESS ? " Pressed":  
            action == GLFW_RELEASE ? " Released": 
            action == GLFW_REPEAT ? " Repeat" : "Unknown"); 
        glfwSetWindowShouldClose(window, GLFW_TRUE); 
    }
}

std::unique_ptr<Controller> Controller::CreateController(const std::string& title, const int width, const int height)
{
    auto controller = std::unique_ptr<Controller> (new Controller()); 
    if(controller && controller->Init(title, width, height) < 0){
        return nullptr; 
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

    glGenVertexArrays(1, &VAO); // VAO를 생성
    glBindVertexArray(VAO); //생성한 VAO를 연결. 

    glGenBuffers(1, &VBO); //VBO 생성
    glBindBuffer(GL_ARRAY_BUFFER, VAO); //생성한 VBO연결.  
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, vertices, GL_STATIC_DRAW); //gpu로 버텍스 배열정보 전달. 

    m_vertexShader=MyShader::ShaderCreate("KShader/simple.vs", GL_VERTEX_SHADER);  
    

    return 1; 
}

void Controller::Run()
{
    uint32_t wWidth =800, wHeight=600; 
    frambufferSize_Callback(m_window, wWidth, wHeight); 
    glfwSetFramebufferSizeCallback(m_window, frambufferSize_Callback); //const int& 에서 기본형으로 변경 에러 없어짐. 
    glfwSetKeyCallback(m_window, keyevent_Callback); 
    
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



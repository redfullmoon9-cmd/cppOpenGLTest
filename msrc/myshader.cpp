#include "myshader.h"

std::unique_ptr<MyShader> MyShader::ShaderCreate(const std::string &fileName, GLenum shaderType)
{
    SPDLOG_INFO("Create Shader "); 
    //C++ 17 스타일로 작성. 이전 코드는 c++ 11로 다시 ... 에러.  
    //static method pattern 으로 생성하면서 자원을 초기화  
    std::unique_ptr<MyShader> shaderPtr= std::unique_ptr<MyShader>(new MyShader()); 
    if(!shaderPtr->ShaderInit(fileName, shaderType) ){
        return nullptr; 
    }
    return std::move(shaderPtr); 
}

MyShader::~MyShader()
{
    if(m_shader) glDeleteShader(m_shader); 
}

//파일을 읽어 오고, 쉐이더를 만들고, 
//쉐이더에 소스 코드를 넘기고 컴파일한다. 
bool MyShader::ShaderInit(const std::string &fileName, GLenum shaderType)
{
    SPDLOG_INFO("Shader Init"); 
    auto result=Header().myLoadTextFile(fileName); 
    if(!result.has_value()) return false; 

    auto& code=result.value(); 
    const char* codePtr=code.c_str(); 

    int32_t codeLength = (int32_t) code.length(); 
    //쉐이더 오브젝트 생성. 
    m_shader = glCreateShader(shaderType); 
    //쉐이더 파일에서 소스를 읽어옴.  
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); 
    //일어온 소스 파일을 컴파일함. 
    glCompileShader(m_shader); 

    int success =0; 
    //컴파일 정보를 얻어옴. 
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); 
    SPDLOG_INFO("Compile info {}", success); 
    //성공하지 않았다면
    if(!success){
        char infoLog[1024]; 
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog); 
        SPDLOG_ERROR(" failed to compile shader {}", fileName); 
        SPDLOG_ERROR(" faile reason {}", infoLog); 
        return false; 
    }

    return true; 

}

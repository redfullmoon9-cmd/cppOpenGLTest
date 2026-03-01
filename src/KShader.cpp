#include "KShader.h"

// private로 되어 있는 생성자를 이곳에서 유일하게 호출한다. 외부에서 반듯이 이 함수를 통해서만 하도록 함.. 
std::unique_ptr<KShader>  KShader::CreateFromFile(const std::string &filename, GLenum shaderType)
{
    // auto shader = std::unique_ptr<KShader>(new KShader()); //매크로 사용으로 아랫것과 동일. 
    auto shader = std::unique_ptr<KShader> (new KShader()); 
    if(!shader-> LoadFile(filename, shaderType)) return nullptr; 
    return std::move(shader); //지역 변수에서 포인터의 소유권을 넘긴다. 
}


bool KShader::LoadFile(const std::string &filename, GLenum shaderType)
{
    auto result = loadTextFile(filename); 
    if(!result.has_value()) return false; 
    
    auto& code = result.value(); 
    const char* codePtr=code.c_str();
    
    int32_t codeLength =(int32_t) code.length(); 
    
    m_shader =glCreateShader(shaderType); //shader object 생성. 
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); //shader에 소스코드 설정. 
    glCompileShader(m_shader); //shader컴파일. 
    
    //컴파일 에러 확인. 
    int success =0; 
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); //shader의 컴파일 상태를 얻어옴. 정수값으로???
    if(!success){
        char infolog[1024]; 
        glGetShaderInfoLog(m_shader, 1024, nullptr, infolog); //shader에 대한 로그을 얻어옴. 컴파일 에러 정보를 가져옴. 
        SPDLOG_ERROR("failed to compile shader : \"{}\"", filename); 
        SPDLOG_ERROR("reason {}", infolog); 
        return false;
    }
    
    return true;
}

KShader::~KShader()
{ 
    if(m_shader) glDeleteShader(m_shader); //shader object제거함. 
}
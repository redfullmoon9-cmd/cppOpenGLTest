#include "common.h"
#include "Program.h"

std::unique_ptr<Program> Program::Create(const std::vector<KShaderPtr> &shaders)
{
    auto program = std::unique_ptr<Program> (new Program()); 
    if(!program->Link(shaders)){
        return nullptr; 
    }
    return std::move(program); //C++17 부터 필요 없다고 C++ 11 하위 호완성. 
}

bool Program::Link(const std::vector<std::shared_ptr<KShader>> &shaders)
{
    m_program =glCreateProgram(); // 
    for(auto& shader:shaders){
        glAttachShader(m_program, shader->Get());  
    }

    glLinkProgram(m_program); 
    
    int success =0; 
    glGetProgramiv(m_program, GL_LINK_STATUS, &success); 
    if(!success){
        char infolog[1024]; 
        glGetProgramInfoLog(m_program, 1024, nullptr, infolog); 
        SPDLOG_ERROR("failed to link program {}", infolog); 
        return false; 
    }
    return true;
}

Program::~Program()
{
    if(m_program) glDeleteProgram(m_program); 
}

void Program::Use() const
{
    glUseProgram(m_program); 
}

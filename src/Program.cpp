#include "common.h"
#include "Program.h"

ProgramUPtr Program::Create(const std::vector<KShaderPtr> &shaders)
{
    auto program = ProgramUPtr(new Program()); 
    if(!program->Link(shaders)){
        return nullptr; 
    }
    return std::move(program); 
}


bool Program::Link(const std::vector<KShaderPtr> &shaders)
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
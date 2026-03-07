#ifndef __PROMRAME_H__
#define __PROMRAME_H__

#include "common.h"
#include "KShader.h"

/** 프로그램과 쉐이더를 연결 
 *  glCreateProgram()
 *  glAttachShader()
 *  glLinkProgram()
 *  glGetProgramiv()
 *  glUseProgram()
 *  glDeleteProgram()
 */

CLASS_PTR(Program); 
class Program{
    public:
        static std::unique_ptr<Program> Create(const std::vector<KShaderPtr>& shaders); 
        ~Program(); 
        uint32_t Get() const { return m_program ; }
        void Use() const; 
    private:
    Program(){}
    bool Link(const std::vector<std::shared_ptr<KShader>>& shaders); 
    uint32_t m_program{0}; 
}; 


#endif //__PROMRAME_H__
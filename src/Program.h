#ifndef __PROMRAME_H__
#define __PROMRAME_H__

#include "common.h"
#include "KShader.h"
CLASS_PTR(Program); 
class Program{
    public:
        static ProgramUPtr Create(const std::vector<KShaderPtr>& shaders); 
        ~Program(); 
        uint32_t Get() const { return m_program ; }
    private:
    Program(){}
    bool Link(const std::vector<KShaderPtr>& shaders); 
    uint32_t m_program{0}; 
}; 


#endif //__PROMRAME_H__
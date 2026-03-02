#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "Program.h"
#include "buffer.h"

// CLASS_PTR(Context)
class Context{
    public:
        static std::unique_ptr<Context> Create(); 
        void Render(); 
        ~Context(){}
    private:
        Context(){}
        bool Init(); 
        // ProgramUPtr m_program; 눈에 잘 않들어와서 길게 쓰기로 . 
        std::unique_ptr<Program> m_program; 

        // uint32_t m_vertexBuffer; -- buffer 클래스로 
        std::unique_ptr<Buffer> m_vertexBuffer; 
        
        // uint32_t m_indexBuffer; 
        std::unique_ptr<Buffer> m_indesBuffer; 
        uint32_t m_vertexArrayObject; 
}; 

#endif //__CONTEXT_H__
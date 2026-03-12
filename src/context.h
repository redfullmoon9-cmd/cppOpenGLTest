#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "Program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

// CLASS_PTR(Context)

/** openGL 함수를 호출 하는 context를 담고 있음. 
 *  1. VAO생성과 설정. 
 *  2. ArrayBuffer 생성 설정... 
 *  3. program 
 *  4. shader 생성
 */
class Context{
    public:
        static std::unique_ptr<Context> Create(); 
        void Render();
        void RenderRef(); //참조용 코드  
        ~Context(){}
    private:
        Context(){}
        bool Init(); 
        bool InitRef(); //참조용 코드. 

        // ProgramUPtr m_program; 눈에 잘 않들어와서 길게 쓰기로 . 
        std::unique_ptr<Program> m_program; 

        // uint32_t m_vertexBuffer; -- buffer 클래스로 
        std::unique_ptr<Buffer> m_vertexBuffer; 
        
        // uint32_t m_indexBuffer; 
        std::unique_ptr<Buffer> m_indexBuffer; 

        // uint32_t m_vertexArrayObject; -- vertexLayout 클래스로 대체 
        std::unique_ptr<VertexLayout> m_vertexlayout; 

        //참조용 코드를 위한 변수 -- 사용하지 않음. 에러 방지. 
        uint32_t m32_vertexArrayObject{0}; 
        uint32_t m32_vertexBuffer{0}; 
        uint32_t m32_indexBuffer{0}; 

        //텍스쳐 아이디 받아오는
        uint32_t m32_texture{ 0 };
        std::unique_ptr<Texture> m_texturePtr;
        //하나의 텍스쳐를 또 사용하기   
        std::unique_ptr<Texture> m_texturePtr2;  
}; 

#endif //__CONTEXT_H__
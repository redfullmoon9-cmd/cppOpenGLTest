#ifndef __KSHADER_H__
#define  __KSHADER_H__

#include "common.h"
#include <memory>

// k대 오픈지엘 강의 -
// 생성자가 private 인 이유: static function안에서만 생성을 할 수 있도록 함. 
// Get은 있는데 Set이 없는 이유 이것도 거의 비슷하게 외부에서 데이터를 조작 할 수 없고 오직 openGL에서만 하도록. 
CLASS_PTR(KShader); 
class KShader{
public:
    static std::unique_ptr<KShader>  CreateFromFile(const std::string& filename, GLenum shaderType); 
    ~KShader(); 
    uint32_t Get() const { return m_shader; }
private:
    KShader(){} 
    bool LoadFile(const std::string& filename, GLenum shaderType ); 
    uint32_t m_shader { 0 }; 
}; 

#endif //__KSHADER_H__
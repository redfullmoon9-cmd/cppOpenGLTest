#ifndef __MYSHADER_H__
#define __MYSHADER_H__

#include "header.h"

/* MyShaer class 기본 기능은 
1. 쉐이더 파일을 읽어온다. -> myLoadTextFile 
2. 쉐이더를 생성한다. -> glCreateShader
3. 쉐이더에게 소스를 전달. -> glShaderSouce
2. 컴파일 한다.  -> glCompileShader 
*/

class MyShader{
public:
    static std::unique_ptr<MyShader> ShaderCreate(const std::string& fileName, GLenum shaderType); 
    ~MyShader(); 
    uint32_t GetShader(){ return m_shader; }; 
private:
    bool ShaderInit(const std::string& fileName, GLenum shaderType); 
    MyShader(){}
    uint32_t m_shader {0};
}; 

#endif //__MYSHADER_H__
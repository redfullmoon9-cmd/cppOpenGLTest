#include "myshader.h"

std::unique_ptr<MyShader> MyShader::ShaderCreate(const std::string &filename)
{
    //C++ 17 스타일로 작성. 이전 코드는 c++ 11 
    // 
    std::unique_ptr<MyShader> shaderPtr= std::make_unique<MyShader>(); 
    if(shaderPtr){
        shaderPtr->ShaderInit(); 
    }
    return std::unique_ptr<MyShader>();
}

MyShader::~MyShader()
{
}

void MyShader::ShaderInit(const std::string &filename)
{
    
}

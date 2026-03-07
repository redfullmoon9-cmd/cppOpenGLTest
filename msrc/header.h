#ifndef __HEADER_H__
#define __HEADER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "spdlog/spdlog.h"

class Header{
    public :
    // KShader/simple.fs 로컬파일을 리딩하는 목적의 공통함수. 
    // optinal은 메모리 동적 할당시에 자동적으로 메모리 해제를 담당하게 해주는 역활.
    // 리턴 타입으로 스트랑 타입의 포인터로 받지만 해제시킬 필요가 없는 포인터를 제공
    std::optional<std::string> myLoadTextFile(const std::string& filename); 

    private:
}; 

#endif //__HEADER_H__
#ifndef COMMON_H 
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>
#include <string>

//std::optional C++17 값이 있을수도 없을 수도 있는 상황을 안전하게 처리. 
std::optional<std::string> loadTextFile(const std::string& filename); 


#endif //COMMON_H
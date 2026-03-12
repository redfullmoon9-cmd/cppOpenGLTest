#ifndef __COMMON_H__ 
#define __COMMON_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <optional>
#include <string>
#include <memory>
// #include <stb/stb_image.h>

//일종의 매크로 인데 std::unique_ptr<Shader> 같은 형태를 줄여 쓰기 위해서 
#define CLASS_PTR(klassName)\
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName  ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPter = std::weak_ptr<klassName> ; 

//std::optional C++17에서 사용됨.  값이 있을수도 없을 수도 있는 상황을 안전하게 처리. 
std::optional<std::string> loadTextFile(const std::string& filename); 


#endif //__COMMON_H__
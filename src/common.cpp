#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> loadTextFile(const std::string& filename) {
    std::ifstream fin(filename); 
    if(!fin.is_open()){
        SPDLOG_INFO(" failed to open file {}", filename); 
        return {};//{}를 붙여주면 아무것도 없는 값이 리턴.  
    }
    std::stringstream text; 
    text << fin.rdbuf(); 
    return text.str(); 
}
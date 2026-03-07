#include "header.h"

std::optional<std::string> Header::myLoadTextFile(const std::string &fileName)
{
    SPDLOG_INFO(" read shader file {}", fileName);  
    std::ifstream fileIn(fileName); 
    if(!fileIn.is_open()){
        SPDLOG_ERROR(" File open error {}", fileName); 
        return {}; //함수반환해야 하는 기본 타입을 반환 여기서 optinal은 아무것도 없는(empty) 값이 됨. 
    }
    std::stringstream text; 
    text << fileIn.rdbuf(); 
    return text.str(); //파일을 열었다면 문자열을 리턴한다. 
}
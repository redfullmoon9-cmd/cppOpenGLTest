#include <iostream>
#include <filesystem>
#include "spdlog/spdlog.h"


//전북대 강의 
namespace orgjOpenGL{ 
    int orgJMain(); 
}

//강원대 강의 
namespace orgkOpenGL{
    int orgKMain(); 
}

//내 코드 
namespace myOpenGL{
    int myMain(); 
}

int main(){
    unsigned int choice =1; 
    if(choice ==0){
        return orgjOpenGL::orgJMain();
    }
    else if(choice ==1){
        // SPDLOG_INFO(" Current execution directory:{}", std::filesystem.current_path()); 
        try {
          std::cout << "현재 디렉토리: " << std::filesystem::current_path() << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout << "경로 오류: " << e.what() << std::endl;
        }
        // std::cout <<" Current execution directory: " << std::filesystem::current_path() <<std::endl; ; 
        return orgkOpenGL::orgKMain(); 
    }
    else if(choice ==2){
        return myOpenGL::myMain(); 
    }
}
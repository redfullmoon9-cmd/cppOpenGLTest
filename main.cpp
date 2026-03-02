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
    unsigned int choice =2; 
    if(choice ==0){
        return orgjOpenGL::orgJMain();
    }
    else if(choice ==1){
        return orgkOpenGL::orgKMain(); 
    }
    else if(choice ==2){
        return myOpenGL::myMain(); 
    }
}
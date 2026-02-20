#include <iostream>

namespace orgOpenGL{ 
    int orgMain(); 
}
namespace myOpenGL{
    int myMain(); 
}

int main(){
    unsigned int choice =0; 
    if(choice ==0){
        return orgOpenGL::orgMain();
    }else if(choice ==1){
        return myOpenGL::myMain(); 

    }
}
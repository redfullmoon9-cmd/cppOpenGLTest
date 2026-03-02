#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "controller.h"

namespace myOpenGL{
    void Render(){

    }
    int myMain(){
        auto controller  =Controller::CreateController("game test", 800, 600); 
        if(controller != nullptr){
            controller->Run(); 
        }
        return 0; 
    }
}
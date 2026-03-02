#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <memory>

class Controller{
    public:
        static std::unique_ptr<Controller> CreateController(const std::string& title, const int width, const int height); 
        int Init(const std::string& title, const int width,  const int height); 
        void Run(); 
        void Render(); 

        void Get(); 

        ~Controller(); 
    private:
        Controller() {} 
        std::unique_ptr<Controller> m_controller; 
        GLFWwindow* m_window=nullptr; 
}; 

#endif //__CONTROLLER_H__
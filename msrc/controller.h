#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <memory>

/** GraphicMyTest 내에 있는 openGL 함수 대부분 이리 옮겨옴. 초기 openGL 환경세팅.  */
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
        // void OnFramBufferSizeChangeCallBack(GLFWwindow* window, const int& width, const int& height); 
}; 

#endif //__CONTROLLER_H__
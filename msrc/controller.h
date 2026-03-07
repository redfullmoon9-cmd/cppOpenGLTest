#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <memory>
#include "myshader.h"

/** GraphicMyTest 내에 있는 openGL 함수 대부분 이리 옮겨옴. 
 * 초기 openGL 환경세팅. init 그리고 run 하면서 main loop 대기  
 * Vertex Buffer Object, Vertext Array Object 생성하고 */
class Controller{
    public:
        static std::unique_ptr<Controller> CreateController(const std::string& title, const int width, const int height); 
        int Init(const std::string& title, const int width,  const int height); 
        void Run(); 
        void Render(); 

        void Get(); 

        ~Controller(); 

        uint32_t VAO{0}; 
        uint32_t VBO{0}; 
    private:
        Controller() {} 
        std::unique_ptr<Controller> m_controller; 
        std::unique_ptr<MyShader> m_vertexShader; 
        std::unique_ptr<MyShader> m_fragmentShader; 
        GLFWwindow* m_window=nullptr; 


}; 

#endif //__CONTROLLER_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 이번에는 Vertex Array와 Shader를 이용하여 삼각형을 그리는 Modern OpenGL 방식으로 구현할 것임
// Vertex Array는 GPU의 VRAM에 Buffer에 저장되는 데이터를 넘기는 방식을 이야기함
// 데이터를 넘기고 나서 삼각형을 실제로 그리는 명령을 호출하는 것을 Draw call이라고 함
// 삼각형이 어떻게 그려질지 사용자가 구현한 프로그램이 Shader임

// OpenGL은 State Machine과 비슷함. 일반적인 객체 지향 프로그램의 설계와는 다르게,
// 현재 처리할 데이터를 선택한 후, 현재 실행해야 할 작업을 함수 호출을 통해 처리하는 방식임
// 간단하게 두 삼각형을 화면에 그리는 의사코드로 설명하면,

// ---객체지향 방식
// Triangle t1, t2; //삼각형 두 개를 정의
// Draw(t1); //t1 객체를 전달함으로써 삼각형 1을 그림
// Draw(t2); //t2 객체를 전달함으로써 삼각형 2를 그림

// ---State Machine 방식
// Triangle t1, t2; //삼각형 두 개를 정의
// Activate(t1); //삼각형 1을 처리중인 상태로 설정
// Draw(); //현재 처리중인 데이터(=삼각형 1)를 화면에 그림
// Activate(t2); //삼각형 2를 처리중인 상태로 설정
// Draw(); //현재 처리중인 데이터(=삼각형 2)를 화면에 그림

namespace orgOpenGL{
    int orgMain(void)
    {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        // glad 방식으로 변경. 
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "GLAD intialized Error\n";
            return -1;
        }

        std::cout << glGetString(GL_VERSION) << std::endl; //내 플랫폼의 GL_Version 출력해보기 //에러 

        //-----Modern OpenGL 방식--------//
        // http://docs.gl/ 에서 아래 gl함수들의 reference를 찾을 수 있음

        float positions[6] = { //삼각형 좌표 정보. 현재는 CPU side memory에 있음
            -0.5f, -0.5f,
            0.0f,  0.5f,
            0.5f, -0.5f,
        };

        //---------데이터를 전달하는 과정--------//
        unsigned int bufferID;
        //1. 데이터를 저장할 버퍼 객체를 만들고(1개), 그 버퍼 객체의 주소를 bufferID에 저장
        glGenBuffers(1, &bufferID); 

        //2. 방금 만든 buffer(두 번째 인자로 주소를 넘겨준)를 "작업 상태"로 만듬
        // 첫 번째 GL_ARRAY_BUFFER는 버퍼에 배열 데이터가 저장될 것이라는 의미
        glBindBuffer(GL_ARRAY_BUFFER, bufferID); //에러 

        //3. 이제 실제로 GPU에 데이터를 넘겨주는 함수를 호출 
        //데이터의 크기를 전달
        //데이터 포인터 전달
        //데이터 변경이 적을 것이라는 것을 알려줌(GPU의 효율적인 동작을 위한 Hint일 뿐)
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions,	GL_STATIC_DRAW);   //에러 

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //----------Modern OpenGL----------//
            // 주의해서 알아야 할 점 : 아래 draw call에서, 삼각형을 그리는 것은
            // 66번째 line에서 glBindBuffer()가 되어 있기 때문임.
            // 아래 glDrawArray에서는 무엇을 그릴 것인지 인자로 넘기는 것이 아니라,
            // 현재 "작업 상태"에 들어와 있는 대상을 그리는 것
            //실제 draw call, 삼각형을 그릴 것이라고 명시
            //몇 번째 데이터부터 그리려는지 명시(모두 그린다면 0)
            //몇 개의 데이터를 그릴 것인지 명시
            glDrawArrays(GL_TRIANGLES, 0, 3);	
            // glfwinit 			
            
            //현재는 아무것도 화면에 나오지 않을 것임. 
            //왜냐하면 삼각형을 어떻게 그릴 것인지 쉐이더를 통해 알려주지 않았기 때문!

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}

#include "context.h"
#include "image.h"

std::unique_ptr<Context>  Context::Create()
{
    auto context = std::unique_ptr<Context> (new Context()); 
    if(!context->Init()){
        return nullptr; 
    }

    return std::move(context); 
}

//attribut변경. position color 
//이전 참조코드 InitRef로 보내고 코드 정리. 
bool Context::Init()
{

    // float vertices[]={
    //     //삼각형 두개를 합처서 그린다. 첫번째 사각형. 
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    //top right red, 
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,    //bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //bottem left
    //     -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f //top left  yellow 
    // }; 
    //텍스쳐를 사용하기 위해서 xyz rgb 텍스텨 코디네이터 값
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    uint32_t indices[] ={
        0, 1, 3, // first trialge 
        1, 2, 3  // second 
    }; 

    m_vertexlayout =VertexLayout::Create(); //VAO 설정 

    //vertices를 buffer에 복사.  vertices에 따라 값이 조정되어야. 
    // m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float)*24); 
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float)*32); //4개의 점에 8개씩.  

    // m_vertexlayout->setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0); //attribue 를 1개에서 2개를 설정하는 것으로 변경. 
    // 몇번째 attriute 인가  몇차원   노말라이즈여부  건널뛸 바이트    초기 옵셋값
    //어트리뷰트별로 하나씩 서정해야함. 
    m_vertexlayout->setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, 0); //attribue 0번 설정. -- 점의 좌표 
    m_vertexlayout->setAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, sizeof(float)*3); //attribue 1번 설정. -현재는 rgb값
    m_vertexlayout->setAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, sizeof(float)*6); //attribue 2번 설정.-- 코디네어터 값 

    m_indexBuffer =Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t)*6); 


    //cmakelists.txt에 구성되어 있는 파일의 위치에서 읽어 오는 방식으로 수정. 
    // -- 갱신시에 build패스에 있는 KShader을 참조하는 문제 때문에..
    std::shared_ptr<KShader> vertexShader = KShader::CreateFromFile(SHADER_DIR "texture.vs", GL_VERTEX_SHADER); 
    std::shared_ptr<KShader> fragmentShader = KShader::CreateFromFile(SHADER_DIR "texture.fs", GL_FRAGMENT_SHADER);

    //create가 성공하면 포인터로 값이 전달되고 없다면 nullptr이 들어 있다. 
    if(!vertexShader || !fragmentShader ){
        return false; 
    } 
    
    SPDLOG_INFO("vertex shader id {}", vertexShader->Get()); // 포인터 주소 -->
    SPDLOG_INFO("fragment shader id {}", fragmentShader->Get()); 
    
    m_program =Program::Create({fragmentShader, vertexShader }); 
    if(!m_program){
        return false; 
    }
    SPDLOG_INFO("program id :{}", m_program->Get()); 
    glClearColor(0.0f, 0.1f, 0.3f, 0.0f);
    
    // 이미지 파일 읽어오는 것 대신에 만들기 테스트 
    // auto image =Image::Create(512, 512); 
    // image->SetCheckImage(16, 16); 
    
    //이미지 파일 읽어오기 
    auto image=Image::Load("KImage/container.jpg"); 
    if(!image) return false; 
    SPDLOG_INFO("image {}x{}, {} channels ", image->GetWidth(), image->GetHeight(), image->GetChannelCount()); 
    
    /** texture관련 코드들 리펙토링으로 이동 */
    //유니크 포인터에 get을 사용하면 쌩포인터 얻어옮. 
    m_texturePtr=Texture::CreateFromImage(image.get()); 

    auto image2=Image::Load("KImage/awesomeface.png"); 
    m_texturePtr2= Texture::CreateFromImage(image2.get()); 

    glActiveTexture(GL_TEXTURE0); //텍스처 슬롯번호를 알려줌. 0번 슬롯. 
    glBindTexture(GL_TEXTURE_2D, m_texturePtr->Get());     
    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, m_texturePtr2->Get());     

    m_program->Use(); 
    glUniform1i(glGetUniformLocation(m_program->Get(), "tex"), 0); 
    glUniform1i(glGetUniformLocation(m_program->Get(), "tex2"), 1); 

    glmTestCode(); 

    return true;
}

bool Context::InitRef()
{
    float vertices[]={
        0.5f, 0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f 
    }; //일단 

    uint32_t indices[] ={ //사각형을 두개의 삼각형으로 그리는 예제에 필요함. 
        0, 1, 3, // first trialge 
        1, 2, 3  // second 
    }; 

    glGenVertexArrays(1, &m32_vertexArrayObject); //VAO 생성. 
    glBindVertexArray(m32_vertexArrayObject); //사용할 VAO 설정. 

    glGenBuffers(1, &m32_vertexBuffer); //VBO
    glBindBuffer(GL_ARRAY_BUFFER, m32_vertexBuffer); 
    //vertices 배열을 buffer에 복사.  
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 12, vertices, GL_STATIC_DRAW); //위에서 지정한 VBO 버퍼에 데이터를 복사. 
    

    //(N) 정점 attribute중 n번째를 사용하도록 설정. KShaer/simple.vs 
    //ayout (location = 0) in vec3 aPos; 내에 location =0 의 0에 해당하는 값
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0); 

    /** index buffer --> buffer class   */
     glGenBuffers(1, &m32_indexBuffer); //인덱스 버퍼를 생성. 
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m32_indexBuffer); //별도로 인덱스 버퍼를 바인딩
     //인덱스 버퍼를 사용해서 두개의 삼각형의 공통지점으로 그린다ㅑ. 
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*6, indices, GL_STATIC_DRAW); 
     
 
    //cmakelists.txt에 구성되어 있는 파일의 위치에서 읽어 오는 방식으로 수정. 
    // -- 갱신시에 build패스에 있는 KShader을 참조하는 문제 때문에..
    //create가 성공하면 포인터로 값이 전달되고 없다면 nullptr이 들어 있다. 
    std::shared_ptr<KShader> vertexShader = KShader::CreateFromFile("KShader/simple.vs", GL_VERTEX_SHADER); 
    std::shared_ptr<KShader> fragmentShader =KShader::CreateFromFile("KShader/simple.fs", GL_FRAGMENT_SHADER); 
    
    if(!vertexShader || !fragmentShader ){
        return false; 
    } 
    
    SPDLOG_INFO("vertex shader id {}", vertexShader->Get()); // 포인터 주소 -->
    SPDLOG_INFO("fragment shader id {}", fragmentShader->Get()); 
    
    m_program =Program::Create({fragmentShader, vertexShader }); 
    if(!m_program){
        return false; 
    }
    SPDLOG_INFO("program id :{}", m_program->Get()); 

    //쉐이더 파일에서 uniform 값을 읽어옴. -- 쉐이더 파일 변경. 
    auto loc =glGetUniformLocation(m_program->Get(),"color" ); //simple.fs의 uniform 변수의 이름. 
    m_program->Use();
    glUniform4f(loc, 1.0f, 1.0f, 0.0f, 1.0f);  //color란 변수가 있는 곳에 loc에 float 값 1.0f, 1.0f ... 등의 값을 입력  

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    
    return true;
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_program->Use(); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //정점 4개와 인덱스를 이용한 사각형. 

}

//참조용 코드. 
void Context::RenderRef()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glPointSize(10.f); // 점찍기 포인트 크기를 크게 하기. 
    // glUseProgram(m_program->Get()); --> Program class 로 변경. 
 
    /** animation start: 시간을 이용해서 RGB값이 변경되는 방식으로 애니메이션 구현*/
    static float time =0.0f ;
    float t= sinf(time) *0.5f + 0.5f; //0에서 1 사이의 값을 얻기 위해서
    auto loc =glGetUniformLocation(m_program->Get(), "color"); 
    m_program->Use(); 
    glUniform4f(loc, t*t, 2.0f *t*(1.0f-t), (1.0f-t)*(1.0f-t), 1.0f); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //정점 4개와 인덱스를 이용한 사각형. 
    time += 0.016f; 
    /*animation  end;  */

    // glDrawArrays(GL_POINTS, 0, 1);  //점그리기 
    // glDrawArrays(GL_TRIANGLES, 0, 3);  // 삼각형 그리기 
    // glDrawArrays(GL_LINE_STRIP, 0, 4);  //점 4개를 연결한 삼각형. 
    // glDrawArrays(GL_TRIANGLES, 0, 6);//점 6개를 그려서 삼각형 2개를 그린다.   

}

void Context::glmTestCode()
{
    // (1, 0, 0) 이라는 점을 동차좌표계로 설정. 
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); 
    //단위 행렬 기준으로 (1, 1, 0) 만큼 이동함. 
    //glm::math4(1.0f) 가 4x4 인 대각행렬을 만들어 내어서 평행 이동하는 vec3 만큼 이동  
    auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f)); 
    //z 축을 기준으로 라디언 값만큼 회전하는 
    auto rotate =glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f)); 

    //각 곱셈은 거꾸로 적용 , scale ->rotate ->trans 순서로 적용됨. 
    //(1, 0, 0) ->scale  (3, 0, 0) -> z 축 rotate --> (0, 3, 0) -> tran --> (1, 4, 0 ) 
    vec = trans* rotate * scale * vec; 
    SPDLOG_INFO("transformed vec:[{} {} {}]", vec.x, vec.y, vec.z); 
    //[2026-03-16 21:48:22.943] [info] [context.cpp:209] transformed vec:[0.9999999 4 0]
}

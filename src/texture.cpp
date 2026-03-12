#include "texture.h"

std::unique_ptr<Texture> Texture::CreateFromImage(const Image *image)
{
    auto texture = std::unique_ptr<Texture> (new Texture()); 
    texture->CreateTexture(); 
    texture->SetTextureFromImage(image); 
    return std::move(texture);
}

Texture::~Texture()
{
    if(m_texture) glDeleteTextures(1, &m_texture); 
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture); //사용하고자 하는 텍스쳐 바인딩. 
}

//각종 파라미터 세팅. - 텍스쳐 필터와 래핑방식등-- 문제 받은 것을 사용하지 않고 
//하드 코딩을 하고 있음. 
void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const
{
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 이전 코드 는 그냥 하드코딩. 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); 
}

void Texture::SetWrap(uint32_t swrap, uint32_t twrap) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
}

//이미지 로딩후 텍스쳐 생성.  
//gpu로 넘어가는 데이터에 각 파라미터를 세팅한다. 
void Texture::CreateTexture()
{
    glGenTextures(1, &m_texture); //텍스쳐오브젝트 생성. 
    Bind();   
    SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);  //MIPMAP 방식의 필터 적용. 
    SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE); 

}

void Texture::SetTextureFromImage(const Image *image)
{
    GLenum format =GL_RGBA; 
    switch(image->GetChannelCount()){
        default:break; 
        case 1: format =GL_RED; break; 
        case 2: format =GL_RG; break; 
        case 3: format = GL_RGB ; break; 
    }

    //실제 cpu안에 들어있는 데이터를 GPU안으로 이동시킴.  
    //각 파라미터 설명: target level 
    //interalFormat -GL_RGB( GL_RED, G L_RG, GL_RGBA8)
    //width height border 
    //format -GL_RGB(입력하는 이미지의 픽셀 포맷) 
    //type- GL_UNSIGNED_BYTE (입력 하는 이미지의 채널별 데이터 타입) 
    //data - image->GetData() (이미지 데이터가 기록된 메모리 주소)
    glTexImage2D(GL_TEXTURE_2D, 0, format, image->GetWidth(), image->GetHeight(), 
        0, format, GL_UNSIGNED_BYTE, image->GetData());  
        
    //작은 이미지를 만들어 준다. 
    glGenerateMipmap(GL_TEXTURE_2D); 
}

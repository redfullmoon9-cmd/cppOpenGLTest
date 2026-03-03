#include "vertex_layout.h"

std::unique_ptr<VertexLayout> VertexLayout::Create()
{
    auto vertexLayout =std::unique_ptr<VertexLayout> (new VertexLayout()); 
    if(vertexLayout){
        vertexLayout->Init(); 
     }
    return std::move(vertexLayout); 
}

VertexLayout::~VertexLayout()
{
    if(m_vertexArrayObject) 
    glDeleteVertexArrays(1, &m_vertexArrayObject); 
}

void VertexLayout::Init()
{
    glGenVertexArrays(1, &m_vertexArrayObject); 
    Bind(); 
}

void VertexLayout::Bind() const
{
    glBindVertexArray(m_vertexArrayObject); 
}

void VertexLayout::setAttribute(uint32_t attribueIndex, int count, uint32_t type, bool normalized, size_t stride, uint64_t offset) const
{
    glEnableVertexAttribArray(attribueIndex); 
    glVertexAttribPointer(attribueIndex, count, type, normalized, stride, (const void*)offset); 

}

void VertexLayout::disableAttribute(int attriuIndex) const
{
}

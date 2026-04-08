#ifndef __VERTEX_LAYOUT_H__
#define __VERTEX_LAYOUT_H__

#include "common.h"

/**  context로부터 관심사별 분리: VAO 관리클래스
 *   Vertext Array Object 관리 클래스  
 *   glGenVertexArrays(1, &m_vertexArrayObject); 
 *   glBindVertexArray()
 *   glEnableVertexAttribArray(attribueIndex); 
 *   glVertexAttribPointer(attribueIndex, count, type, normalized, stride, (const void*)offset); 
 */

// CLASS_PTR(VertexLayout)
class VertexLayout{
public:
    static std::unique_ptr<VertexLayout> Create(); 
    ~VertexLayout(); 
    void Bind() const; 
    uint32_t Get() const { return m_vertexArrayObject; }
    void setAttribute(uint32_t attribueIndex, int count, uint32_t type, bool normalized, size_t stride, uint64_t offset) const; 
    void disableAttribute(int attriuIndex ) const; 
private:
    VertexLayout() {}
    void Init(); 
    uint32_t m_vertexArrayObject{ 0 }; 
}; 

#endif //__VERTEX_LAYOUT_H__
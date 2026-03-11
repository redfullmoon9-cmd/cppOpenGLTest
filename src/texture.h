#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// #include "common.h"
#include <memory>
#include "image.h"

class Texture{
public :
    static std::unique_ptr<Texture> CreateFromImage(const Image* image); 
    ~Texture(); 
private:
    Texture(){}
 };

#endif //__TEXTURE_H__
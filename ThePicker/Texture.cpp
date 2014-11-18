//
//  ThePicker
//  Texture.cpp
//
//  Helps handle setting up and binding texture
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Texture.h"
#include <assert.h>

Texture::Texture(const char * file)
{
    FIBITMAP * dib = NULL;
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file, 0);
    
	if( fif == FIF_UNKNOWN )
    {
		fif = FreeImage_GetFIFFromFilename(file);
	}
    
	if( (fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif))
    {
	  dib = FreeImage_Load(fif, file, 0);
		assert(dib);	
	}
    
    FIBITMAP * bitmap = dib;
    assert(bitmap);
    
    FREE_IMAGE_COLOR_TYPE fic = FreeImage_GetColorType(bitmap);
    assert( fic == FIC_RGB || fic == FIC_RGBALPHA );
    
    unsigned int bpp = FreeImage_GetBPP(bitmap);
    assert(bpp == 24 || bpp == 32);
    
    GLenum pixelFormat;
    if(bpp == 24)
    {
        pixelFormat = GL_RGB;
    }
    else
    {
        pixelFormat = GL_RGBA;
    }
    
    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
		
    glGenTextures(1, &_textureID);
    bind( );
		
    // glTexEnv is deprecated in Core profile
    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));

}

Texture::~Texture()
{
	glDeleteTextures(1, &_textureID);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

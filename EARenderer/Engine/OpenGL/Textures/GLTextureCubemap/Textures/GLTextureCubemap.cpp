//
//  GLTextureCubemap.cpp
//  EARenderer
//
//  Created by Pavlo Muratov on 21.04.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#include "GLTextureCubemap.hpp"
#include "stb_image.h"

#include <stdexcept>

namespace EARenderer {
    
#pragma mark - Lifecycle

    GLTextureCubemap::GLTextureCubemap()
    :
    EARenderer::GLTexture(GL_TEXTURE_CUBE_MAP)
    { }

    GLTextureCubemap::~GLTextureCubemap() { };

    void GLTextureCubemap::initialize(const Size2D& size, Sampling::Filter filter, Sampling::WrapMode wrapMode,
                                      GLint internalFormat, GLenum format, GLenum type,
                                      std::array<const void *, 6>& pixelData)
    {
        mSize = size;

        for(GLuint i = 0; i < 6; i++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, size.width,
                         size.height, 0, format, type, pixelData[i]);
        }

        setFilter(filter);
        setWrapMode(wrapMode);
    }

}

//
//  ScreenSpaceReflectionEffect.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 15.07.2018.
//  Copyright © 2018 MPO. All rights reserved.
//

#ifndef ScreenSpaceReflectionEffect_hpp
#define ScreenSpaceReflectionEffect_hpp

#include "GLSLScreenSpaceReflections.hpp"
#include "PostprocessTexturePool.hpp"
#include "SceneGBuffer.hpp"
#include "Camera.hpp"
#include "GaussianBlurEffect.hpp"

#include <memory>

namespace EARenderer {

    class ScreenSpaceReflectionEffect {
    private:
        GLSLScreenSpaceReflections mSSRShader;
        GaussianBlurEffect mBlurEffect;

        void renderReflections(const Camera& camera,
                               std::shared_ptr<const GLFloatTexture2D<GLTexture::Float::RGBA16F>> lightBuffer,
                               std::shared_ptr<const SceneGBuffer> GBuffer,
                               std::shared_ptr<GLFloatTexture2D<GLTexture::Float::RGBA16F>> mirrorReflections,
                               std::shared_ptr<PostprocessTexturePool> texturePool);

        void blurReflections(std::shared_ptr<GLFloatTexture2D<GLTexture::Float::RGBA16F>> mirrorReflections,
                             std::shared_ptr<PostprocessTexturePool> texturePool);

        void performConeTracing(const Camera& camera,
                                std::shared_ptr<const GLFloatTexture2D<GLTexture::Float::RGBA16F>> inputImage,
                                std::shared_ptr<const SceneGBuffer> GBuffer,
                                std::shared_ptr<GLFloatTexture2D<GLTexture::Float::RGBA16F>> outputImage,
                                std::shared_ptr<PostprocessTexturePool> texturePool);

    public:
        void applyReflections(const Camera& camera,
                              std::shared_ptr<const GLFloatTexture2D<GLTexture::Float::RGBA16F>> lightBuffer,
                              std::shared_ptr<const SceneGBuffer> GBuffer,
                              std::shared_ptr<GLFloatTexture2D<GLTexture::Float::RGBA16F>> outputImage,
                              std::shared_ptr<PostprocessTexturePool> texturePool);
    };

}

#endif /* ScreenSpaceReflectionEffect_hpp */

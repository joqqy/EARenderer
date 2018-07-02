//
//  GaussianBlurEffect.cpp
//  EARenderer
//
//  Created by Pavel Muratov on 6/14/18.
//  Copyright © 2018 MPO. All rights reserved.
//

#include "GaussianBlurEffect.hpp"
#include "GaussianFunction.hpp"

#include <stdexcept>

namespace EARenderer {

#pragma mark - Lifecycle

    GaussianBlurEffect::GaussianBlurEffect(std::shared_ptr<const GLHDRTexture2D> inputImage,
                                           std::shared_ptr<GLFramebuffer> sharedFramebuffer)
    :
    PostprocessEffect(sharedFramebuffer),
    mInputImage(inputImage),
    mFirstOutputImage(std::make_shared<GLHDRTexture2D>(inputImage->size())),
    mSecondOutputImage(std::make_shared<GLHDRTexture2D>(inputImage->size()))
    {
        sharedFramebuffer->attachTexture(*mFirstOutputImage);
        sharedFramebuffer->attachTexture(*mSecondOutputImage);
    }

#pragma mark - Getters

    std::shared_ptr<GLHDRTexture2D> GaussianBlurEffect::outputImage() const {
        return mSecondOutputImage;
    }

#pragma mark - Blur

    void GaussianBlurEffect::computeWeightsAndOffsets() {
        auto weights = GaussianFunction::Produce1DKernel(mSettings.radius, mSettings.sigma);

        mWeights.clear();
        mTextureOffsets.clear();

        // Kernel's center
        mWeights.push_back(weights[0]);
        mTextureOffsets.push_back(0.0);

        // Calculate texture offsets and combined weights to make advantage of hardware interpolation
        for (size_t i = 1; i <= mSettings.radius; i += 2) {
            float weight1 = weights[i];
            float weight2 = weights[i + 1];
            float totalWeight = weight1 + weight2;

            float texOffset1 = i;
            float texOffset2 = i + 1;

            float texOffset = (texOffset1 * weight1 + texOffset2 * weight2) / totalWeight;

            mWeights.push_back(totalWeight);
            mTextureOffsets.push_back(texOffset);
        }
    }

    std::shared_ptr<GLHDRTexture2D> GaussianBlurEffect::blur(const GaussianBlurSettings& settings) {
        if (settings.radius == 0) throw std::invalid_argument("Blur radius must be greater than 0");

        if (settings != mSettings) {
            bool isOdd = settings.radius % 2 == 1;
            mSettings.radius = isOdd ? settings.radius + 1 : settings.radius;
            mSettings.sigma = settings.sigma;
            computeWeightsAndOffsets();
        }

        mSharedFramebuffer->bind();
        mSharedFramebuffer->viewport().apply();

        mBlurShader.bind();
        mBlurShader.setKernelWeights(mWeights);
        mBlurShader.setTextureOffsets(mTextureOffsets);
        mBlurShader.ensureSamplerValidity([&]() {
            mBlurShader.setTexture(*mInputImage);
        });

        mBlurShader.setBlurDirection(GLSLGaussianBlur::BlurDirection::Horizontal);

        mSharedFramebuffer->redirectRenderingIntoAttachedTexture(*mFirstOutputImage);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        mBlurShader.setBlurDirection(GLSLGaussianBlur::BlurDirection::Vertical);

        mBlurShader.ensureSamplerValidity([&]() {
            mBlurShader.setTexture(*mFirstOutputImage);
        });

        mSharedFramebuffer->redirectRenderingIntoAttachedTexture(*mSecondOutputImage);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        return mSecondOutputImage;
    }

}

//
//  GLBlinnPhongProgram.cpp
//  EARenderer
//
//  Created by Pavlo Muratov on 11.04.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#include "GLBlinnPhongProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace EARenderer {
    
    void GLBlinnPhongProgram::setCameraPosition(const glm::vec3& position) {
        glUniform3fv(uniformLocation("uCameraPosition"), 1, glm::value_ptr(position));
    }
    
    void GLBlinnPhongProgram::setLightPosition(const glm::vec3& position) {
        glUniform3fv(uniformLocation("uLightPosition"), 1, glm::value_ptr(position));
    }
    
    void GLBlinnPhongProgram::setCameraSpaceMatrix(const glm::mat4& matrix) {
        glUniformMatrix4fv(uniformLocation("uCameraSpaceMat"), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    void GLBlinnPhongProgram::setLightSpaceMatrix(const glm::mat4& matrix) {
        glUniformMatrix4fv(uniformLocation("uLightSpaceMat"), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    void GLBlinnPhongProgram::setModelMatrix(const glm::mat4& matrix) {
        glUniformMatrix4fv(uniformLocation("uModelMat"), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    void GLBlinnPhongProgram::setNormalMatrix(const glm::mat4& matrix) {
        glUniformMatrix4fv(uniformLocation("uNormalMat"), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void GLBlinnPhongProgram::setLightColor(const glm::vec3 &color) {
        glUniform3fv(uniformLocation("uLightColor"), 1, glm::value_ptr(color));
    }
    
    void GLBlinnPhongProgram::setMaterial(const Material& material)
    {
        glUniform3fv(uniformLocation("uMaterial.ambientReflectances"), 1, glm::value_ptr(material.ambientReflectances()));
        glUniform3fv(uniformLocation("uMaterial.diffuseReflectances"), 1, glm::value_ptr(material.diffuseReflectances()));
        glUniform3fv(uniformLocation("uMaterial.specularReflectances"), 1, glm::value_ptr(material.specularReflectances()));
        glUniform1f(uniformLocation("uMaterial.specularExponent"), material.specularExponent());
        
        setUniformTexture("uMaterial.diffuseTexture", material.skin());
    }
    
    void GLBlinnPhongProgram::setShadowMap(const GLDepthTexture2D& shadowMap) {
        setUniformTexture("uShadowMap", shadowMap);
    }
    
    void GLBlinnPhongProgram::setHighlighted(bool isHighlighted) {
        glUniform1i(uniformLocation("isHighlighted"), GLint(isHighlighted));
    }
    
}

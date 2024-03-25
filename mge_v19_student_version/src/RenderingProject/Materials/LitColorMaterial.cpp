#include "glm.hpp"

#include "LitColorMaterial.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"

#include "RenderingProject/config.hpp"


namespace RP {
    MGE::ShaderProgram* LitColorMaterial::_shader = NULL;

    LitColorMaterial::LitColorMaterial(glm::vec3 pDiffuseColor) :_diffuseColor(pDiffuseColor)
    {
        //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
        _lazyInitializeShader();
    }

    void LitColorMaterial::_lazyInitializeShader() {
        //this shader contains everything the material can do (it can render something in 3d using a single color)
        if (!_shader) {
            _shader = new MGE::ShaderProgram();
            _shader->addShader(GL_VERTEX_SHADER, config::RP_SHADER_PATH + "litcolor.vs");
            _shader->addShader(GL_FRAGMENT_SHADER, config::RP_SHADER_PATH + "litcolor.fs");
            _shader->finalize();
        }
    }

    LitColorMaterial::~LitColorMaterial()
    {
        //dtor
    }

    void LitColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
        _diffuseColor = pDiffuseColor;
    }

    void LitColorMaterial::render(MGE::World* pWorld, MGE::Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
        _shader->use();

        //set the material color
        glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));

        //pass in all MVP matrices separately
        glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
        glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
        glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

        glUniform1f(_shader->getUniformLocation("ambientIntensity"), 1.0f);
        glUniform3fv(_shader->getUniformLocation("ambientLightColor"), 1, glm::value_ptr(_ambientLightColor));
        glUniform3fv(_shader->getUniformLocation("lightColor"), 1, glm::value_ptr(_lightColor));
        glUniform3fv(_shader->getUniformLocation("lightPosition"), 1, glm::value_ptr(_lightPosition));
        //now inform mesh of where to stream its data
        pMesh->streamToOpenGL(
            _shader->getAttribLocation("vertex"),
            _shader->getAttribLocation("normal"),
            _shader->getAttribLocation("uv")
        );

    }
}
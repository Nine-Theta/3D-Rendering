#ifndef LITCOLORMATERIAL_HPP
#define LITCOLORMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"

namespace MGE {
    class ShaderProgram;
}
    /**
     * This is about the simplest material we can come up with, it demonstrates how to
     * render a single color material without caching, passing in all the matrices we require separately.
     */
namespace RP {
    class LitColorMaterial : public MGE::AbstractMaterial
    {
    public:
        LitColorMaterial(glm::vec3 pDiffuseColor = glm::vec3(1, 0, 0), glm::vec4 pAmbientColor = glm::vec4(1, 1, 1, 1), glm::vec3 pLightColor = glm::vec3(1, 1, 1), glm::vec3 pLightPosition = glm::vec3(0, 0, 0));
        virtual ~LitColorMaterial();

        virtual void render(MGE::World* pWorld, MGE::Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        //in rgb values
        void setDiffuseColor(glm::vec3 pDiffuseColor);

        void setLightPosition(glm::vec3 pLightPos);

    private:
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static MGE::ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;

        glm::vec3 _ambientLightColor;
        glm::vec3 _lightColor;
        glm::vec3 _lightPosition;
        glm::vec3 _attenuationConstant;

        float _ambientIntensity;
    };
}
#endif // COLORMATERIAL_HPP

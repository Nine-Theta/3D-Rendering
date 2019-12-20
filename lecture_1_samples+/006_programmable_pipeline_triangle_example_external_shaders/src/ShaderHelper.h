#ifndef SHADERHELPER_H
#define SHADERHELPER_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class ShaderHelper
{

public:
	void InitModel(GLuint& pProgramID, GLuint& pVertexBufferId, GLuint& pColorBufferId,sf::Window& pWindow);

private:
	float rotation = 0;
	float scale = 1;
	sf::Clock sClock;
};

#endif
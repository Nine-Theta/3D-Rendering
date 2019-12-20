#include "ShaderHelper.h"


float rotation = 0;
float scale = 1;
sf::Clock sClock;

void ShaderHelper::InitModel(GLuint& pProgramID, GLuint& pVertexBufferId, GLuint& pColorBufferId, sf::Window& pWindow) {
	
	glClear(GL_COLOR_BUFFER_BIT);

	//tell the GPU to use this program
	glUseProgram(pProgramID);

	//offset
	float elapsedTime = sClock.getElapsedTime().asSeconds();
	glUniform2f(glGetUniformLocation(pProgramID, "offset"), 0.5f * cos(elapsedTime), 0.5f * sin(elapsedTime));

	glUniform1f(glGetUniformLocation(pProgramID, "time"), elapsedTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		scale += +0.002f;
	else if (scale > 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		scale -= 0.002f;

	glUniform1f(glGetUniformLocation(pProgramID, "scale"), scale);

	glUniform2f(glGetUniformLocation(pProgramID, "mousePos"), sf::Mouse::getPosition().x - pWindow.getPosition().x, sf::Mouse::getPosition().y - pWindow.getPosition().y);

	glUniform2f(glGetUniformLocation(pProgramID, "screenSize"), pWindow.getSize().x, pWindow.getSize().y);

	glUniform1f(glGetUniformLocation(pProgramID, "time"), elapsedTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rotation += +0.002f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rotation -= 0.002f;

	glUniform2f(glGetUniformLocation(pProgramID, "rotation"), sin(rotation), cos(rotation));

	//get index for the attributes in the shader
	GLint vertexIndex = glGetAttribLocation(pProgramID, "vertex");
	GLint colorIndex = glGetAttribLocation(pProgramID, "color");
	//GLint mousePosIndex = glGetAttribLocation(pProgramID, "mousePos");

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(vertexIndex);
	glEnableVertexAttribArray(colorIndex);

	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//send the data for this index to OpenGL, specifying it's format and structure
	//colorIndex // 3 bytes per element // floats // don't normalize // the data itself
	glBindBuffer(GL_ARRAY_BUFFER, pColorBufferId);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(vertexIndex);
	glDisableVertexAttribArray(colorIndex);
}

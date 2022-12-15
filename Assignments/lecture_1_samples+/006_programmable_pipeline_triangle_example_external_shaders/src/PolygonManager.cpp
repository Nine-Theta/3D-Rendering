#include "PolygonManager.h"
#include <iostream>

PolygonManager::PolygonManager(GLuint pProgramID)
{
	programID = pProgramID;
}


/////////////////////////////////////////////////ARRAY_DRAW////////////////////////////////////////////////////////////////


GLuint PolygonManager::BufferArrayTriangles(GLfloat & pVerts, GLuint pByteSize) {

	//std::cout << "vertbuffer: " + std::to_string(pVerts.size() * sizeof(GLfloat)) + '\n';

	//create a handle to the buffer
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, pByteSize, &pVerts, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vertexBufferId;
}


GLuint PolygonManager::BufferArrayColors(GLfloat & pColors, GLuint pByteSize) {

	//create a handle to the buffer
	GLuint colorBufferId;
	glGenBuffers(1, &colorBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex color data will be created
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	//stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
	//note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, pByteSize, &pColors, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	return colorBufferId;
}


void PolygonManager::RenderModel(GLuint pVertexBuffer, GLuint pColorBuffer, GLsizei pVertCount) {

	//get index for the attributes in the shader
	GLint vertexIndex = glGetAttribLocation(programID, "vertex");
	GLint colorIndex = glGetAttribLocation(programID, "color");

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(vertexIndex);
	glEnableVertexAttribArray(colorIndex);

	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//send the data for this index to OpenGL, specifying it's format and structure
	//colorIndex // 3 bytes per element // floats // don't normalize // the data itself
	glBindBuffer(GL_ARRAY_BUFFER, pColorBuffer);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLES, 0, pVertCount);

	//std::cout << "pvertbuffer: " + std::to_string(pVertexBuffer) + '\n';


	glDisableVertexAttribArray(vertexIndex);
	glDisableVertexAttribArray(colorIndex);
}


/////////////////////////////////////////////////ELEMENT_DRAW////////////////////////////////////////////////////////////////


GLuint PolygonManager::BufferElementTriangles(GLfloat& pVerts, GLuint pByteSize) {

	//create a handle to the buffer
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pByteSize, &pVerts, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return vertexBufferId;
}


GLuint PolygonManager::BufferElementColors(GLfloat& pColors, GLuint pByteSize) {

	//create a handle to the buffer
	GLuint colorBufferId;
	glGenBuffers(1, &colorBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex color data will be created
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	//stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
	//note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, pByteSize, &pColors, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	return colorBufferId;
}


void PolygonManager::RenderModelAlt(GLsizei pVertCount, const GLvoid* pIndices) {

	//get index for the attributes in the shader
	GLint vertexIndex = glGetAttribLocation(programID, "vertex");
	GLint colorIndex = glGetAttribLocation(programID, "color");

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(vertexIndex);
	glEnableVertexAttribArray(colorIndex);

	glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, pIndices);

	//std::cout << "pvertbuffer: " + std::to_string(pVertexBuffer) + '\n';


	glDisableVertexAttribArray(vertexIndex);
	glDisableVertexAttribArray(colorIndex);
}
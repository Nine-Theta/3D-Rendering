#ifndef POLYGONMANAGER_H
#define POLYGONMANAGER_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>


class PolygonManager
{

public:
	PolygonManager(GLuint pProgramID);
	GLuint BufferArrayTriangles (GLfloat & pVerts, GLuint pByteSize);
	GLuint BufferArrayColors (GLfloat & pColors, GLuint pByteSize);

	GLuint BufferElementTriangles(GLfloat& pVerts, GLuint pByteSize);
	GLuint BufferElementColors(GLfloat& pColors, GLuint pByteSize);

	void RenderModel(GLuint pVertexBuffer, GLuint pColorBuffer, GLsizei pVertCount);
	void RenderModelAlt(GLsizei pVertCount, const GLvoid* pIndices);


private:
	GLuint programID;
};

#endif


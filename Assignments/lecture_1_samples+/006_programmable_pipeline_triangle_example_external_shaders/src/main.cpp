#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ShaderUtil.h"
#include "PolygonManager.h"

/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */

int main() {
	//Open SFML Window == Valid OpenGL Context
	sf::Window window(
		sf::VideoMode(800, 600),       //800 x 600 x 32 bits pp
		"OpenGL Window",                //title
		sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
		sf::ContextSettings(
			24,                         //24 bits depth buffer, important for 3D!
			0,                          //no stencil buffer
			0,                          //no anti aliasing
			3,                          //requested major OpenGL version
			3                           //requested minor OpenGL version
		)
	);

	window.setVerticalSyncEnabled(true);

	//initialize glew to load all available opengl functions/extensions
	GLenum glewResult = glewInit();
	if (glewResult != GLEW_OK) {
		std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
		return -1;
	}

	//Create the shader program
	//GLuint programID = ShaderUtil::createProgram("vertexshader.vert", "fragmentshader.frag");
	//GLuint programID = ShaderUtil::createProgram("vertcheckers.vert", "fragcheckers.frag");
	GLuint programID = ShaderUtil::createProgram("vertLight.vert", "fragLight.frag");

	PolygonManager manager(programID);

	//declare the data to upload
	GLfloat vertices[]{
		//1 triangle, 3 vertices per triangle, 3 floats per vertex = 9 floats in total
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		-0.5f, 0.5f, 0,
		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0,
		-0.5f, 0.5f, 0
	};

	GLuint vertBufferId = manager.BufferArrayTriangles(*vertices, sizeof(vertices));

	GLfloat colors[]{
		//1 triangle, 3 vertices per triangle, 1 color per vertex, 3 "floats" per color RGB = 9 floats in total
		1,0,0,
		0,1,0,
		0,0,1,
		0,1,0,
		0,1,1,
		0,0,1
	};

	GLuint colorBufferId = manager.BufferArrayColors(*colors, sizeof(colors));


	sf::Clock clock;

	float size = 2;
	float angle = 45;

	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition();

	glClearColor(0, 0, 0, 1);
	while (window.isOpen()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			size += 0.005f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			size -= 0.005f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			angle += 0.005f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			angle -= 0.005f;
		
		mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

		mouse.x /= window.getSize().x;
		mouse.y /= window.getSize().y;

		std::cout << mouse.x << std::endl;


		glClear(GL_COLOR_BUFFER_BIT);

		

		//tell the GPU to use this program
		glUseProgram(programID);

		//offset
		float elapsedTime = clock.getElapsedTime().asSeconds();
		//glUniform2f(glGetUniformLocation(programID, "offset"), 0.5f * cos(elapsedTime), 0.5f * sin(elapsedTime));
		glUniform1f(glGetUniformLocation(programID, "size"), size);
		glUniform1f(glGetUniformLocation(programID, "angle"), angle);
		glUniform3f(glGetUniformLocation(programID, "mouse"), mouse.x, 1 - mouse.y, sqrt(mouse.x*mouse.x + mouse.y*mouse.y));

		//manager.RenderModel(vertexBufferId,colorBufferId,3);
		manager.RenderModel(vertBufferId, colorBufferId, 6);

		//display it
		window.display();

		//empty the event queue
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
		}

	}

	return 0;
}



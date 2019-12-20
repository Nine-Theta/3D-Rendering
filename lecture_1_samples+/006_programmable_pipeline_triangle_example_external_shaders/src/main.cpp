#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ShaderUtil.h"
#include "ShaderHelper.h"

/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */



int main () {
    //Open SFML Window == Valid OpenGL Context
    sf::Window window(
        sf::VideoMode (800, 600),       //800 x 600 x 32 bits pp
        "OpenGL Window",                //title
        sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
        sf::ContextSettings (
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
	GLuint programID = ShaderUtil::createProgram("vertexshader_two.vs", "fragmentshader_rotate.fs");
	GLuint programID2 = ShaderUtil::createProgram("vertexshader_three.vs", "fragmentshader_anim.fs");

	//declare the data to upload
	const GLfloat vertices[] = {
		//1 triangle, 3 vertices per triangle, 3 floats per vertex = 9 floats in total
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		-0.5f, 0.5f, 0,

		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0,
		-0.5f, 0.5f, 0
	};

	//create a handle to the buffer
	GLuint vertexBufferId, vertexBufferId2;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &vertexBufferId2);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    const GLfloat colors[] {
        //1 triangle, 3 vertices per triangle, 1 color per vertex, 3 "floats" per color RGB = 9 floats in total
        1,0,0,
        0,0,0,
        1,1,0,

		0,0,0,
		0,1,0,
		1,1,0
    };

	//create a handle to the buffer
	GLuint colorBufferId;
	glGenBuffers(1, &colorBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex color data will be created
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	//stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
	//note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	sf::Clock clock;

	ShaderHelper shaderHelper;

    glClearColor(0, 0, 0, 1);
    while (window.isOpen()) {
		
		shaderHelper.InitModel(programID, vertexBufferId, colorBufferId, window);
		shaderHelper.InitModel(programID2, vertexBufferId2, colorBufferId, window);

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
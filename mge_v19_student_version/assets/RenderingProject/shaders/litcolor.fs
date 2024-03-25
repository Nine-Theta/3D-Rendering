//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 ambient;
in vec3 diffuse;

//uniform vec3 diffuseColor;

out vec4 fragment_color;

void main( void ) {
	//fragment_color = vec4 (diffuseColor,1);
	fragment_color = vec4 (ambient,1);
}

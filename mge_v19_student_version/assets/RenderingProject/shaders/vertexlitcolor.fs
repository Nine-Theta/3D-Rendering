//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
in vec3 fColor;

out vec4 fragment_color;

void main( void ) {
	//fragment_color = vec4 (ambient,1);
	//fragment_color = vec4 (diffuse,1);
	fragment_color = vec4 (specular,1);
	//fragment_color = vec4 (fColor,1);
}

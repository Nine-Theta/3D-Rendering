//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

in float ambientIntensity;
in vec3 ambientLightColor;
in vec3 diffuseColor;

in vec3 lightPosition;
in vec3 lightColor;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

out vec3 ambient;
out vec3 diffuse;

void main( void ){
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);

        ambient = ambientIntensity * ambientLightColor * diffuseColor;

        //diffuse = max(dot((vertex - lightPosition),normal),0) * lightColor * diffuseColor;
}

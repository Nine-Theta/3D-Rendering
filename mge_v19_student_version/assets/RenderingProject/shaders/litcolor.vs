//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform float ambientIntensity;

uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 attenConstant;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform	mat3 	normalModelMatrix;

out vec3 ambient;
out vec3 diffuse;
out vec3 fColor;

void main( void ){
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);

        ambient = ambientIntensity * ambientLightColor;

        vec3 vertNormal = normalize(normalModelMatrix * normal);

        //vec3 vertest = vec3(projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 0.f)); 

        vec3 vertPos = vec3(modelMatrix * vec4(vertex, 1.f));

        vec3 lightDir = normalize(lightPosition - vertPos);

        diffuse = max(dot(lightDir, vertNormal), 0) * lightColor;
        
        float lightDist = length(lightPosition - vertPos);
        vec3 attenuation = diffuse / (attenConstant.x + (attenConstant.y * lightDist) + (attenConstant.z * lightDist * lightDist));

        fColor = (ambient + attenuation) * diffuseColor; 
}



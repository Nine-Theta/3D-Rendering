//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform vec3 ambientLight;
uniform vec3 diffuseColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 attenConstant;

uniform vec3 cameraPosition;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform	mat3 	normalModelMatrix;

out vec3 ambient;
out vec3 diffuse;
out vec3 specular;
out vec3 fColor;


void main( void ){
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);

        ambient = ambientLight;

        vec3 vertNormal = normalize(normalModelMatrix * normal);

        //vec3 vertest = vec3(projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 0.f)); 

        vec3 vertPos = vec3(modelMatrix * vec4(vertex, 1.f));

        vec3 lightDir = normalize(lightPosition - vertPos);

        diffuse = max(dot(lightDir, vertNormal), 0) * lightColor;
        
        float lightDist = length(lightPosition - vertPos);
        vec3 attenuation = diffuse / (attenConstant.x + (attenConstant.y * lightDist) + (attenConstant.z * lightDist * lightDist));

        vec3 camDir = normalize(cameraPosition - vertPos);
        vec3 reflectDir = reflect(-lightDir, vertNormal);
        
        specular = pow(max(dot(camDir, reflectDir), 0), 16) * lightColor;

        fColor = (ambient + attenuation + specular) * diffuseColor; 
}
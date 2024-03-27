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

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform	mat3 	normalModelMatrix;

out vec3 ambient;
out vec3 diffuse;
out vec3 fColor;


vec3 Q_normalize(vec3 vector);
float Q_length(vec3 vector);
float Q_rsqrt(vec3 vector);
float Q_rsqrt(float number);


void main( void ){
        gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);

        ambient = ambientLight;

        vec3 vertNormal = Q_normalize(normalModelMatrix * normal);

        vec3 vertPos = vec3(modelMatrix * vec4(vertex, 1.f));

        vec3 lightDir = Q_normalize(lightPosition - vertPos);

        diffuse = max(dot(lightDir, vertNormal), 0) * lightColor;
        
        float lightDist = Q_length(lightPosition - vertPos);
        vec3 attenuation = diffuse / (attenConstant.x + (attenConstant.y * lightDist) + (attenConstant.z * lightDist * lightDist));

        fColor = (ambient + attenuation) * diffuseColor; 
}

vec3 Q_normalize(vec3 vector) {
        return vector * Q_rsqrt(vector);
}

float Q_length(vec3 vector) {
        float x = vector.x + vector.y + vector.z;
        x = x * x;
        return x * Q_rsqrt(x);
}

float Q_rsqrt(vec3 vector) {
        vec3 vec = vector * vector;
        return Q_rsqrt(vec.x + vec.y + vec.z);
}

float Q_rsqrt(float number) {
        int i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y  = number;
        i  = floatBitsToInt(y);                         // evil floating point bit level hacking
        i  = 0x5f3759df - ( i >> 1 );                   // what the fuck?
        y  = intBitsToFloat(i);
        y  = y * ( threehalfs - ( x2 * y * y ) );       // 1st iteration
        // y  = y * ( threehalfs - ( x2 * y * y ) );    // 2nd iteration, this can be removed

        return y;
}


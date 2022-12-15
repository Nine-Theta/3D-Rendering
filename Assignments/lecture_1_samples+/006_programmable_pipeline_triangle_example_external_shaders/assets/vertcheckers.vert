#version 330

in vec3 vertex;
in vec3 color;
uniform vec2 offset;
uniform float size;

out vec3 fColor;
out vec2 fPosition;
out vec2 fSize;

void main (void) {

    gl_Position = vec4(vertex,1) + vec4(offset,0,0);
    
    fPosition = vertex.xy + vec2(0.5,0.5);
    fColor = color;
        
    fSize.x = size*0.5;
    fSize.y = 1/(size*0.5);
}


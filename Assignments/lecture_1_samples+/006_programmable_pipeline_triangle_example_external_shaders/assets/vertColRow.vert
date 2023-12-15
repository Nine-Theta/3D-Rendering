#version 330

in vec3 vertex;
in vec3 color;
uniform vec2 offset;
uniform vec2 array;
uniform float size;

out vec3 fColor;
out vec2 fPosition;
out vec2 fSize;
out vec2 fCols;
out vec2 fRows;


void main (void) {

    gl_Position = vec4(vertex,1) + vec4(offset,0,0);
    
    fPosition = vertex.xy + vec2(0.5,0.5);
    fColor = color;
        
    fCols.x = 2/array.x;
    fCols.y = array.x*.5;

    fRows.x = 2/array.y;
    fRows.y = array.y*.5;
}


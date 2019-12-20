#version 330

in vec3 vertex;
in vec3 color;

uniform vec2 offset;
uniform vec2 mousePos;
uniform vec2 screenSize;
uniform vec2 rotation;

uniform float time;
uniform float scale;

//-----out-----

out vec3 fColor;
out vec3 fVertex;

out vec2 fOffset;
out vec2 fMousePos;
out vec2 fScreenSize;
out vec2 fRotation;

out float fTime;
out float fScale;

void main (void) {

    gl_Position =  vec4(vertex,1) + vec4(offset,0,0);

    fColor = color;
    fVertex = vertex;
    fOffset = offset;
    fMousePos = mousePos;
    fScreenSize = screenSize;
    fRotation = rotation;
    fTime = time;
    fScale = scale;
}


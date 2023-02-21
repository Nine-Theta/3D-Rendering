#version 330

in vec3 vertex;
in vec3 color;
uniform vec2 offset;
uniform float size;
uniform float angle;
uniform vec3 mouse;
uniform float lightMult;

out vec3 fColor;
out vec2 fPosition;
out vec2 fScreenPosition;
out vec2 fSize;
out vec2 fAngle;
out vec3 fMouse;
out float fLightMult;

void main (void) {

    gl_Position = vec4(vertex,1)+ vec4(offset,0,0);
    fColor = color;

    fPosition = vertex.xy ;
    fScreenPosition = (vertex.xy + offset + 1) *0.5;

    fSize.x = size*0.5;
    fSize.y = 1/(size*0.5);

    fAngle.x = sin(angle);
    fAngle.y = cos(angle);

    fMouse = mouse;

    fLightMult = lightMult;
}


#version 330

in vec3 fColor;
in vec3 fVertex;

in vec2 fOffset;
in vec2 fMousePos;
in vec2 fScreenSize;
in vec2 fRotation;

in float fTime;
in float fScale;

out vec4 sColor;

void main (void) {
    float rx = fVertex.x * fRotation.x - fVertex.y * fRotation.y;
    float ry = fVertex.y * fRotation.x + fVertex.x * fRotation.y;
    
    float x = round(mod(rx * fScale, 1));
    float y = round(mod(ry * fScale, 1));

    float s = 0;
    if (x == y) { s = 1; }

    vec2 mouse = fMousePos / (fScreenSize * 0.5f) - 1;
    mouse.y = -mouse.y;

    float d = 1 - (length(mouse - (fVertex.xy + fOffset)));    
    s = s * d;

    sColor = vec4(s, s, s, 1);
}


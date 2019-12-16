#version 330

in vec3 fColor;
in vec3 fVertex;
in vec2 fOffset;

out vec4 sColor;

void main (void) {
    float x = round(mod(fVertex.x *4, 1));
    float y = round(mod(fVertex.y *4, 1));
    float s = 0;
    if (x == y) { s = 1; }

    sColor = vec4(s, s , s, 1);
}


#version 330

in vec3 fColor;
in vec3 fVertex;
in vec2 fOffset;

out vec4 sColor;

void main (void) {
    float r = round(mod(fVertex.r *4, 1));
    float g = round(mod(fVertex.g *4, 1));
    float s = 0;
    if (r == g) { s = 1; }

    sColor = vec4(s, s , s, 1);
}


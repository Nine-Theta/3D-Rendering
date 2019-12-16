#version 330

in vec3 fColor;
in vec3 fVertex;

in vec2 fOffset;
in vec2 fMove;
in vec2 fMousePos;
in vec2 fScreenSize;

in float fTime;
in float fScale;

out vec4 sColor;

void main (void) {
    vec2 vertex = vec2(fVertex+0.5f);
    vertex += fOffset;

    float x = round(mod(fVertex.x * fScale, 1));
    float y = round(mod(fVertex.y * fScale, 1));
    float s = 0;
    if (x == y) { s = 1; }

    float q = fMousePos.x / fScreenSize.x;
    //if(vertex.x > 1) vertex.x = mod(vertex.x, 1);

    float m = (q - vertex.x);
    //float p = 1-q;
    //if(m > 1){ p = 1-(m-1);}

    //float my = (fMousePos.x / fScreenSize.x) - fVertex.y;
    //if(vertex.x > 1){ p = 1; }
    

    sColor = vec4(m, 0, 0, 1);
}


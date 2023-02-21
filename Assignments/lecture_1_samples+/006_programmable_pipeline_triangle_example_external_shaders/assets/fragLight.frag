#version 330

in vec3 fColor;
in vec2 fPosition;
in vec2 fScreenPosition;
in vec2 fSize;
in vec2 fAngle;
in vec3 fMouse;

in float fLightMult;

out vec4 sColor;

void main (void) {

   float x = fPosition.x;
   float y = fPosition.y;

   vec2 pos;

   pos.x = x*fAngle.y - y*fAngle.x;
   pos.y = x*fAngle.x + y*fAngle.y;

   x = mod(pos.x, fSize.y)*fSize.x;
   y = mod(pos.y, fSize.y)*fSize.x;

   y = round(y);
   x = round(x);   

   float checkers = mod(x+y,2);

   float delta = abs(fScreenPosition.x - fMouse.x) + abs(fScreenPosition.y - fMouse.y);

   float lightPattern = (1 - (delta * fLightMult));


    sColor = vec4(lightPattern * checkers * fColor,1);
}


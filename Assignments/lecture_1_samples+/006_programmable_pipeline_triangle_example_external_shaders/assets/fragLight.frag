#version 330

in vec3 fColor;
in vec2 fPosition;
in vec2 fSize;
in vec2 fAngle;
in vec3 fMouse;

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

   float z = fColor.x*fColor.y;

   

   float q = mod(x+y,2);

   float f = fMouse.x - fPosition.x;
   float r = fPosition.y - fMouse.y;
   float g = f*r;

   q = q+fMouse.x*fMouse.y-1.3;


    sColor = vec4(q,q,q,1) * vec4(fColor,1);


}


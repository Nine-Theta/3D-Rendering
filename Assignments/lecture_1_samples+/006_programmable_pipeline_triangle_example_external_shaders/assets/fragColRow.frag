#version 330

in vec3 fColor;
in vec2 fPosition;
in vec2 fCols;
in vec2 fRows;

out vec4 sColor;

void main (void) {

   float x = fPosition.x;
   float y = fPosition.y;

   x = mod(x, fCols.x)*fCols.y;
   y = mod(y, fRows.x)*fRows.y;


   //y = fSize.y;


   //x = mod(x, fSize.y)*fSize.x;
   //y = mod(y, fSize.y)*fSize.x;

   y = round(y);
   x = round(x);

   
   //x = mod(x, 0.5);

   

   float q = mod(x+y,2);
   //q = mod(q, );

    sColor = vec4(q,q,q,1);

    //sColor = vec4(fPosition,0,1);

    //sColor = vec4(fColor,1);


}


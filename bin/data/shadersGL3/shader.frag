#version 150

uniform sampler2DRect tex0;
uniform sampler2DRect colormap;

in vec2 texCoordVarying;

in vec2 vUv;
out vec4 outputColor;
 
void main()
{
  
    outputColor = texture(colormap, texCoordVarying);
}
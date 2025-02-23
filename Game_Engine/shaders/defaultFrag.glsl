#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) uniform uint colorID;
layout(location = 1) out vec4 fragColor;

void main() {
    float redColor = float (0x000000FF & colorID) /255.0;
    float greenColor = float ((0x0000F00 & colorID)>>8) /255.0;
    float blueColor = float ((0x00FF0000 & colorID)>>16) /255.0;
    float alphaColor = 0.0;
    fragColor = vec4(redColor,greenColor,blueColor,alphaColor); 
}
#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 inVertex;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUVCoord;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 eyeDir;
layout(location = 2) out vec3 lightDir;
layout(location = 3) out vec2 texCoord;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;
layout(location = 3) uniform vec3 lightPos;


void main() {
    texCoord = inUVCoord;
    texCoord.y *= -1.0;
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vertNormal = normalize(normalMatrix * inNormal);
    vec3 vertPos = vec3(viewMatrix * modelMatrix * inVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir = normalize(lightPos - vertPos);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * inVertex;
}
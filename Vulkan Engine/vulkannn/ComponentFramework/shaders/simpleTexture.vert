#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texureCoord;

layout(std140, binding = 0) uniform UniformBufferObject {
    mat4 projection;
    mat4 view;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;



layout(location = 1) out vec2 texCoord;

void main() {
    texCoord = texureCoord;
    gl_Position = ubo.projection * ubo.view * push.modelMatrix * vertex;
   
}
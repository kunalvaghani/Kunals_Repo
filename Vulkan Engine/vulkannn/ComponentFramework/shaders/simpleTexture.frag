#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D textureSampler;

layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = texture(textureSampler, texCoord);
}
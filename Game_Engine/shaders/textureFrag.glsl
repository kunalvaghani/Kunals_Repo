#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 eyeDir;
layout(location = 2) in vec3 lightDir;
layout(location = 3) in vec2 texCoord;

layout(location = 0) out vec4 fragColor;

uniform sampler2D skullTexture;

void main() {
    vec4 ks = vec4(0.3 , 0.3 , 0.3 , 0.0);
    vec4 kd = vec4(0.0 , 0.0 , 0.0 , 0.0);
    vec4 kTexture = texture(skullTexture , texCoord);
    kTexture *= 0.5;
    vec4 ka= 0.1 * kd;
    float diff = max(dot(lightDir , vertNormal) , 0.0);
    vec3 reflection = reflect(-lightDir , vertNormal);
    float spec = max(dot(eyeDir , reflection), 0.0);
    spec = pow(spec , 14.0);
    fragColor = ka + (diff * (kTexture + kd))+ (ks * spec);
}
#version 450
#extension GL_ARB_separate_shader_objects : enable
#define MAX_LIGHTS 3

layout (location = 0) in vec3 vertNormal;
layout (location = 1) in vec3 lightDir[MAX_LIGHTS];
layout (location = 5) in vec3 eyeDir; 
layout (location = 6) in vec2 uvCoord;

layout (location = 0) out vec4 fragColor;

layout(binding = 1) uniform lightUniformBufferObject {
    vec4 position[MAX_LIGHTS];
    vec4 diffuse[MAX_LIGHTS];
    uint numberoflights;
} lightubo;

layout(binding = 2 )uniform sampler2D myTexture;


void main() {
    vec4 ks[3] = {vec4(0.5f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.5f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.5f, 0.0f)};
    //vec4 kd[3] = {vec4(0.1, 0.1, 0.1, 0.0),vec4(0.2f, 0.2f, 0.2f, 0.0f), vec4(0.3f, 0.3f, 0.3f, 0.0f)};
	vec4 kd = vec4(0.0, 0.0, 0.1, 0.0);
   
    vec4 kt = texture(myTexture, uvCoord);
     vec4 ka = 0.2 * kd *kt;

    vec4 finalColor = vec4(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++) {
        float diff = max(dot(vertNormal, lightDir[i]), 0.0);
        vec3 reflection = normalize(reflect(-lightDir[i], vertNormal));
        float spec = max(dot(eyeDir, reflection), 0.0);

        if (diff > 0.0) {
            spec = pow(spec, 14.0);
        }

        finalColor += (diff * ks[i] * kd) + (spec * ks[i]);
    }

    fragColor = ka +kt + finalColor;
}


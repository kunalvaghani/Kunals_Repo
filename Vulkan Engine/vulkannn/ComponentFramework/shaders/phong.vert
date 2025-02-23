#version 450
#extension GL_ARB_separate_shader_objects : enable
#define MAX_LIGHTS 3

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
	mat4 normalMatrix;
} push;

layout( binding = 0) uniform UniformBufferObject {
    mat4 projectionMatrix;
    mat4 viewMatrix;
} cameraubo;

layout(binding = 1) uniform lightUniformBufferObject {
    vec4 position[MAX_LIGHTS];
    vec4 diffuse[MAX_LIGHTS];
    uint numberoflights;
} lightubo;


layout (location = 0) out vec3 vertNormal;
layout (location = 1) out vec3 lightDir[MAX_LIGHTS];
layout (location = 5) out vec3 eyeDir;
layout (location = 6) out vec2 uvCoord;



void main() {

	 uvCoord = textureCoord;
    vertNormal = mat3(push.normalMatrix) * normal; // Rotate the normal to the correct orientation
    vec3 vertPos = vec3(cameraubo.viewMatrix * push.modelMatrix * vertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;

    lightDir[0] = vec3(12.0, 15.0, 0.0);
    lightDir[1] = vec3(-12.0, 12.0, 0.0);
    lightDir[2] = vec3(0.0, 14.0, 0.0);

    gl_Position = cameraubo.projectionMatrix * cameraubo.viewMatrix * push.modelMatrix * vertex; 
}


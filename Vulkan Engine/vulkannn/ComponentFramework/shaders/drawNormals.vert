#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;

layout (std140, binding = 0) uniform CameraMatricies {
    mat4 projection;
    mat4 view;
};

layout(push_constant) uniform Push {
	mat4 modelMatrix;
	mat4 normalMatrix;
} push;


layout (location = 0) out VertexStage {
    vec3 normal;
} vs_out;



void main() {
    gl_Position = view * push.modelMatrix * vVertex;
    vs_out.normal = mat3(push.normalMatrix) * vNormal;
}
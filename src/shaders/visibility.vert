#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 viewProj;
} ubo;

layout(location = 0) in vec3 inPosition;

void main() 
{
    gl_Position = ubo.viewProj * vec4(inPosition.xzy * 0.01, 1.0);
}
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 viewProj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
    gl_Position = ubo.viewProj * vec4(inPosition.xzy * 0.01, 1.0);
}
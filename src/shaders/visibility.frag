#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) out uint outVisibility;

void main() 
{
    outVisibility = gl_PrimitiveID;
}
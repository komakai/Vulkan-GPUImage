#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
layout (binding = 0) uniform sampler2D tex;
layout (location = 0) in vec2 texcoord;
layout (location = 0) out vec4 uFragColor;

layout (push_constant) uniform haze {
 float distance;
 float slope;
} pushVals;

void main() {
    vec4 color = vec4(1.0);
    float d = texcoord.y * pushVals.slope + pushVals.distance;
    vec4 textureColor = texture(tex,  texcoord); 
    textureColor = (textureColor - d * color) / (1.0 - d);
    uFragColor = textureColor;
}
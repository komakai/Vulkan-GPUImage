#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
layout (binding = 0) uniform sampler2D tex;

layout (push_constant) uniform pushBlock {
 float push_red;
 float push_green;
 float push_blue;
} pushVals;

layout (location = 0) in vec2 texcoord;
layout (location = 0) out vec4 uFragColor;

void main() {
    vec4 textureColor = texture(tex,  texcoord); 
    uFragColor = vec4(textureColor.r * pushVals.push_red, textureColor.g * pushVals.push_green , textureColor.b * pushVals.push_blue,1.0);
}

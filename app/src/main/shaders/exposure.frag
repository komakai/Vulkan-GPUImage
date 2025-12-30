#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
layout (binding = 0) uniform sampler2D tex;
layout (location = 0) in vec2 texcoord;
layout (location = 0) out vec4 uFragColor;

layout (push_constant) uniform exposure {
 float exposure;
} pushVals;

void main() {
    vec4 textureColor = texture(tex,  texcoord); 
    uFragColor = vec4(textureColor.rgb * pow(2.0,pushVals.exposure),textureColor.w);
}
#version 450

#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UboObject
{
	vec4 transform;
	vec4 colourOffset;
	vec2 atlasOffset;
	float atlasRows;
	float alpha;
} object;

layout(binding = 1) uniform sampler2D samplerTexture;

layout(location = 0) in vec2 fragmentTextures;

layout(location = 0) out vec4 outColour;

void main(void) 
{
	outColour = texture(samplerTexture, fragmentTextures) * vec4(object.colourOffset.rgb, 1.0);
	outColour.a *= object.alpha;

	if (outColour.a < 0.05)
	{
		outColour = vec4(0.0);
		discard;
	}
}

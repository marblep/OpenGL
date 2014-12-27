#version 130

out vec4 vFragColor;

uniform samplerCube cubeMap;
smooth in vec3 vVaryingTexCoord;

void main(void)
{
	vFragColor = texture(cubeMap, vVaryingTexCoord.stp);
}
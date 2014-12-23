#version 130

out vec4 vFragColor;

uniform samplerCube cubeMap;

in vec3 vTexCoord;

void main(void)
{
	vFragColor = texture(cubeMap, vTexCoord);
}
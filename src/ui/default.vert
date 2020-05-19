#version 330

layout(location = 0) in vec2 vertexPos2D;
//layout(location = 1) in vec2 vertexTex2D;
layout(location = 2) in vec3 vertexColor3D;

out vec4 vertexColor;

uniform vec2 translate;
uniform vec2 mapScale;
uniform float objectScale;

void main() {
	gl_Position = vec4(
        mapScale.x*(objectScale*vertexPos2D.x + translate.x),
        mapScale.y*(objectScale*vertexPos2D.y + translate.y),
        0, 1);
	vertexColor = vec4(vertexColor3D, 1);
}

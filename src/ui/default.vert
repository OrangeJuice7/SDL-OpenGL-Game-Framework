#version 330

layout(location = 0) in vec2 vertexPos2D;
layout(location = 1) in vec2 vertexTex2D;
layout(location = 2) in vec4 vertexColor4D;

out vec2 textureCoord;
out vec4 vertexColor;

uniform vec2 translate;
uniform vec2 mapScale;
uniform float objectScale;

void main() {
	gl_Position = vec4( mapScale*(objectScale*vertexPos2D + translate), 0, 1);

	textureCoord = vertexTex2D;

	vertexColor = vertexColor4D;
}

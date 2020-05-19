#version 330

in vec2 textureCoord;
in vec4 vertexColor;

out vec4 fragColor;

uniform sampler2D texture2d;

void main() {
	fragColor = texture(texture2d, textureCoord) * vertexColor;
}

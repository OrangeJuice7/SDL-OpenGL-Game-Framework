#version 330

in vec2 textureCoord;
in vec4 vertexColor;

out vec4 fragColor;

uniform sampler2D texture2d;
uniform uint flags;

const uint SHADER_FLAG_RENDER_TEXT = uint(1 << 0);

bool hasFlag(uint flag) {
    return (flags & flag) != 0u;
}

void main() {
	vec4 textureColor = texture(texture2d, textureCoord);

	if (hasFlag(SHADER_FLAG_RENDER_TEXT)) // Rendering text
        fragColor = vec4(vertexColor.rgb, vertexColor.a * textureColor.r);
    else
        fragColor = textureColor * vertexColor;
}

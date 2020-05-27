#version 330

layout(location = 0) in vec2 vertexPos2D;
layout(location = 1) in vec2 vertexTex2D;
layout(location = 2) in vec4 vertexColor4D;

out vec2 textureCoord;
out vec4 vertexColor;

uniform vec2 coordToScreenScale;
uniform vec2 objectTranslate;
uniform vec2 objectScale;
uniform vec3 colorMask;
uniform uint flags;

const uint SHADER_FLAG_RENDER_TEXT = uint(1 << 0);

bool hasFlag(uint flag) {
    return (flags & flag) != 0u;
}

void main() {
	vec2 pos = vertexPos2D;

	// Scale the object (if it's not text)
	if (!hasFlag(SHADER_FLAG_RENDER_TEXT))
        pos *= objectScale;

    // Translate in map coords (pixels for ortho mode)
    pos += objectTranslate;

    // Scale from pixels (for ortho) or map coords (otherwise) to OpenGL screen coords
    pos *= coordToScreenScale;

    // Set gl_Position
    gl_Position = vec4(pos, 0, 1);

	textureCoord = vertexTex2D;

	vertexColor = vec4(vertexColor4D.rbg * colorMask, vertexColor4D.a);
}

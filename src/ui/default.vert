#version 330

layout(location = 0) in vec2 vertexPos2D;
layout(location = 1) in vec2 vertexTex2D;
layout(location = 2) in vec4 vertexColor4D;

out vec2 textureCoord;
out vec4 vertexColor;

uniform vec2 screenDimensions;
uniform vec2 translate;
uniform float mapScale;
uniform vec2 objectScale;
uniform uint flags;

const uint SHADER_FLAG_ORTHO_MODE = uint(1 << 0);
const uint SHADER_FLAG_RENDER_TEXT = uint(1 << 1);

bool hasFlag(uint flag) {
    return (flags & flag) != 0u;
}

void main() {
	vec2 pos = vertexPos2D;

	// Scale the object (if it's not text)
	if (!hasFlag(SHADER_FLAG_RENDER_TEXT))
        pos *= objectScale;

    // Translate in map coords (pixels for ortho mode)
    pos += translate;

    // If it's orthographic, it's already in pixels. Otherwise, scale from map coords to pixels
	if (!hasFlag(SHADER_FLAG_ORTHO_MODE))
        pos *= mapScale;

    // Scale from pixels to OpenGL screen coords
	// x2 because OpenGL by default takes the window to be coords -1 to 1, i.e. the window is 2 coords wide in each direction
    pos /= screenDimensions / 2.f;

    // If orthographic, translate to bottom left corner
	if (hasFlag(SHADER_FLAG_ORTHO_MODE))
        pos -= vec2(1, 1);

    // Set gl_Position
    gl_Position = vec4(pos, 0, 1);

	textureCoord = vertexTex2D;

	vertexColor = vertexColor4D;
}

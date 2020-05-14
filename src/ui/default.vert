#version 330

layout(location = 0) in vec2 vertexPos2D;
//layout(location = 1) in vec2 vertexTex2D;
layout(location = 2) in vec3 vertexColor3D;

out vec4 vertexColor;

void main() {
	gl_Position = vec4(vertexPos2D, 0, 1);
	vertexColor = vec4(vertexColor3D, 1);
	//vertexColor = vec4(1.f, .5f, .0f, 1.f);
	//vertexColor = .5f*(gl_Position + vec4(1,1,0,1));
}

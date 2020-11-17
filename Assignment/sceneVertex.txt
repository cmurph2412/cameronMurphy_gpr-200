#version 300 es

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModelMat, uViewMat, uProjMat;

out vec4 vNormal;

void main()
{
	gl_Position = uProjMat * uViewMat * uModelMat * aPosition;
	
	vNormal = vec4(aNormal, 0.0);
}
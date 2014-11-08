# version 120

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

varying vec4 color;
varying vec3 myNormal;
varying vec4 myVertex;

void main() {
	gl_Position = ProjectionMatrix * ModelViewMatrix * gl_Vertex;
	color = gl_Color;
	myNormal = gl_Normal;
	myVertex = gl_Vertex;
}

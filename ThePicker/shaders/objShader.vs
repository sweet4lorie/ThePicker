# version 120

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

varying vec3 lightDir;
varying float intensity;

varying vec3 myNormal;
varying vec4 myVertex;

void main() {
    lightDir = vec3(-0.7, 0.6, 0.0);
    intensity = dot(lightDir,gl_Normal);
    
	gl_Position = ProjectionMatrix * ModelViewMatrix * gl_Vertex;
	myNormal = gl_Normal;
	myVertex = gl_Vertex;
}

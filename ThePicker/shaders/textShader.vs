# version 120

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

void main(){
  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
  gl_Position = ProjectionMatrix * ModelViewMatrix * ftransform();
}

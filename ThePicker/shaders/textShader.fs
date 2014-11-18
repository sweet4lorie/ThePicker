# version 120

uniform sampler2D texture;
uniform vec4 color;

void main(){
  vec4 colorTex = texture2D(texture, gl_TexCoord[0].st);
  gl_FragColor = colorTex * color;
}


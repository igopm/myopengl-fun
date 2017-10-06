#version 330 core

in vec2 pTexCoord;

out vec4 color;

uniform sampler2D uTex;

void main(){
    color = texture(uTex, pTexCoord);
}

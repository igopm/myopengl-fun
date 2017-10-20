#version 330 core

in vec2 pTexCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main(){
    color = texture(ourTexture1, pTexCoord);
}

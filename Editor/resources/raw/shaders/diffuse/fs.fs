#version 330 core
out vec4 color;
in vec2 p_TextureCoords;
uniform sampler2D u_textureDiffuse;
void main(){
	//color = vec4(1.0);
	color = texture(u_textureDiffuse, p_TextureCoords);
}
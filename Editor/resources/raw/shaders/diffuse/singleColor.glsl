#VS

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

void main(){
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
}

#FS
#version 330 core
out vec4 color;
void main(){
	color = vec4(1.0);
	//color = texture(u_textureDiffuse, p_TextureCoords);
}
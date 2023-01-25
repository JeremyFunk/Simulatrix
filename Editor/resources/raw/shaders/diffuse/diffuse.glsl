#VS

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
out vec2 p_TextureCoords;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

void main(){
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
	p_TextureCoords = a_TexCoords;
}

#FS
#version 330 core
layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_entityId;
uniform int u_entityId;
in vec2 p_TextureCoords;
uniform sampler2D u_textureDiffuse;
void main(){
	o_Color = texture(u_textureDiffuse, p_TextureCoords);
	o_entityId = u_entityId;
}
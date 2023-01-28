#VS

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoords;
out float p_Depth;
out vec2 p_TextureCoords;
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

void main(){
	gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_Position, 1.0);
	p_TextureCoords = a_TexCoords * 1.001 - .0005;
	p_Depth = gl_Position.w;
}

#FS
#version 330 core
layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_Selection;
in vec2 p_TextureCoords;
in float p_Depth;

float grid(vec2 st, float res)
{
    vec2 grid = fract(st);
    return step(res, grid.x) * step(res, grid.y);
}

void main(){
	float far = 100.0;
	float depth = p_Depth / far;
	float offset = 1.0 - depth;

    vec2 mUv = p_TextureCoords;
    vec2 tUv = fract(mUv * 20.0);
    tUv = abs(tUv - 0.5) * 2.0;

    float grid = max(tUv.x, tUv.y);
    grid = smoothstep(1.0, offset, grid);
	
	o_Color = vec4(vec3(0.95), 0.5) * (1.0 - grid);
	
	o_Selection = -1;
}	
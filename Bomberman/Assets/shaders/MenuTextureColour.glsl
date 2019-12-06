#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Rot;
uniform mat4 u_Model;

void main() {
	gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
	v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
    v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
	color = vec4(texture(u_Texture, v_TexCoord).rgb, 1.0);
}
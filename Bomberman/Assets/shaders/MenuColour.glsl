#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Rot;
uniform mat4 u_Model;

void main() {
	gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
	v_Normal = normalize(u_Rot * vec4(a_Normal, 0.0)).xyz;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Normal;

uniform vec4 u_Color = vec4(0.6, 0.1, 0.5, 1.0);

void main() {
	color = u_Color;
}
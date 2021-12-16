#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 v_worldPos;
out vec3 v_normal;
out vec2 v_texCoord;

void main()
{
    gl_Position = u_proj * u_view * u_model * position;
    v_worldPos = mat3(u_model) * position.xyz;
    v_normal = mat3(u_model) * normal;
    v_texCoord = texCoord;
}
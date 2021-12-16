#version 400 core

layout(location = 0) out vec4 color;

in vec3 v_worldPos;
in vec3 v_normal;
in vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec3 u_lightLoc;

void main()
{
    vec3 ambientLight = vec3(0.05, 0.05, 0.05);

    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_lightLoc - v_worldPos);
    float diffuse = clamp(dot(normal, lightDir), 0.0, 1.0);
    vec3 diffuseLight = vec3(1.0, 1.0, 1.0);
    diffuseLight *= diffuse;

    color = texture(u_texture, v_texCoord) * vec4((ambientLight + diffuseLight), 1.0);
}
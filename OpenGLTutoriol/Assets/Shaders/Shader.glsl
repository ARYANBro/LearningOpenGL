#shader vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoords;

out vec4 v_Color;
out vec2 v_TexCoords;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    v_TexCoords = a_TexCoords;

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0f);
 }

#shader fragment
#version 460 core

out vec4 fragColor;

in vec4 v_Color;
in vec2 v_TexCoords;

uniform sampler2D u_PavingStonesTexture;
uniform sampler2D u_FabricTexture;

void main()
{
    fragColor = mix(texture(u_PavingStonesTexture, v_TexCoords), texture(u_FabricTexture, v_TexCoords), 0.1f);
}

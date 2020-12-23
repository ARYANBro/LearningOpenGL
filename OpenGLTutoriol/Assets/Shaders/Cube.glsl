#shader vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0f);
}

#shader fragment
#version 460 core

out vec4 fragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

void main()
{
    const float ambientStrength = 0.1f;
    fragColor = vec4(ambientStrength * u_LightColor * u_ObjectColor, 1.0f);
}

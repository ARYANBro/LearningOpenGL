#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

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

uniform vec4 u_Color;

void main()
{
    fragColor = u_Color;
}

#shader vertex
#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec4 vColor;

void main()
{
    vColor = vec4(aColor, 1.0f);
    gl_Position = vec4(aPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec4 vColor;

void main()
{
    FragColor = vColor;
}

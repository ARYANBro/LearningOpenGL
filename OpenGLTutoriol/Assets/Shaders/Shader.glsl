#shader vertex
#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec4 vColor;
out vec2 vTexCoords;

void main()
{
    vColor = vec4(aColor, 1.0f);
    vTexCoords = aTexCoords;

    gl_Position = vec4(aPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec4 vColor;
in vec2 vTexCoords;

uniform sampler2D uPavingStonesTexture;
uniform sampler2D uFabricTexture;

void main()
{
    FragColor = mix(texture(uPavingStonesTexture, vTexCoords), texture(uFabricTexture, vTexCoords), 0.2f);
}

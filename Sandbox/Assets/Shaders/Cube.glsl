#shader vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

out vec3 v_Normal;
out vec3 v_FragPosition;
out vec3 v_LightPosition;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform vec3 u_LightPosition;

void main()
{
    v_FragPosition = vec3(u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0f));
    v_Normal = inverse(transpose(mat3(u_ViewMatrix * u_ModelMatrix))) * a_Normal;
    v_LightPosition = vec3(u_ViewMatrix * vec4(u_LightPosition, 1.0f));

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0f);
}

#shader fragment
#version 460 core

out vec4 fragColor;

in vec3 v_Normal;
in vec3 v_FragPosition;
in vec3 v_LightPosition;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

uniform float u_SpecularStrength = 1.0f;
uniform int u_Shininess = 16;
uniform float u_AmbientStrength;

uniform bool u_EnableDiffuse;
uniform bool u_EnableSpecular;
uniform bool u_EnableAmbient;

vec3 CalculateAmbient(float strength, vec3 color)
{
    return strength * color;
}

vec3 CalculateDiffuse(vec3 lightDirection, vec3 fragPosition, vec3 normal, vec3 lightColor)
{
    float diffuseAmount = max(dot(normal, lightDirection), 0.0f);

    return diffuseAmount * lightColor;
}

vec3 CalculateSpecular(vec3 fragPosition, vec3 normal, vec3 lightDirection, float strength, int shininess)
{
    float normalDot = dot(normal, lightDirection);

    if (normalDot > 0.0f)
    {
        vec3 viewDirection = normalize(-fragPosition);
        vec3 reflectDir = reflect(-lightDirection, normal);
        float specularAmount = pow(max(dot(reflectDir, viewDirection), 0.0f), shininess);

        return specularAmount * u_LightColor * max(strength, 0.0f);
    }
}

void main()
{
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(v_LightPosition - v_FragPosition);

    vec3 ambient = CalculateAmbient(u_AmbientStrength, u_LightColor);
    vec3 diffuse = CalculateDiffuse(lightDirection, v_FragPosition, normal, u_LightColor);
    vec3 specular = CalculateSpecular(v_FragPosition, normal, lightDirection, u_SpecularStrength, u_Shininess);

    vec3 color = vec3(0.0f);

    if (u_EnableAmbient || u_EnableDiffuse || u_EnableSpecular)
    {
        if (u_EnableAmbient)
        {
            color += ambient;
        }

        if (u_EnableDiffuse)
        {
            color += diffuse;
        }

        if (u_EnableSpecular)
        {
            color += specular;
        }

        color *= u_ObjectColor;
    }
    else
    {
        color = u_ObjectColor * u_LightColor;
    }
    

    fragColor = vec4(color, 1.0f);
}

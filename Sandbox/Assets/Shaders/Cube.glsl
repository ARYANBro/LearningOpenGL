#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

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

uniform bool u_EnableDiffuse;
uniform bool u_EnableSpecular;
uniform bool u_EnableAmbient;

struct MaterialProperties
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct LightProperties
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform LightProperties u_LightProps;
uniform MaterialProperties u_MaterialProps;

vec3 CalculateAmbient(vec3 color)
{
    return u_LightProps.Ambient * color;
}

vec3 CalculateDiffuse(vec3 lightDirection, vec3 fragPosition, vec3 normal, vec3 objectColor)
{
    float diffuseAmount = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
    return u_LightProps.Diffuse * diffuseAmount * objectColor;
}

vec3 CalculateSpecular(vec3 fragPosition, vec3 normal, vec3 lightDirection, float shininess, vec3 color)
{
    if (dot(normal, lightDirection) > 0.0f)
    {
        vec3 viewDirection = normalize(-fragPosition);
        vec3 reflectDir = reflect(-lightDirection, normal);
        float specularAmount = pow(clamp(dot(reflectDir, viewDirection), 0.0f, 1.0f), shininess);
        return u_LightProps.Specular * specularAmount * color;
    }
}

void main()
{
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(v_LightPosition - v_FragPosition);

    vec3 ambient = CalculateAmbient(u_MaterialProps.Ambient);
    vec3 diffuse = CalculateDiffuse(lightDirection, v_FragPosition, normal, u_MaterialProps.Diffuse);
    vec3 specular = CalculateSpecular(v_FragPosition, normal, lightDirection, u_MaterialProps.Shininess, u_MaterialProps.Specular);

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}

#version 460

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in VS_OUT {
    vec4 relativePos;
	float transp;
} gs_in[];

out GS_OUT
{
    float transp;
    vec3 color;
} gs_out;

/* Material */
struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float reflectivity;
    float shineDamper;
    bool isTextured;
};

/* Lights */
struct BaseLight
{
    vec3 color;
    float intensity;
    bool castShadow;
};

struct DirectionalLight
{
    BaseLight baseLight;
    vec3 direction;
};

struct PointLight
{
    BaseLight baseLight;
    vec3 position;
    float constAtt;
    float linearAtt;
    float quadraticAtt;
};

struct SpotLight
{
    PointLight pointLight;
    vec3 direction;
    float cutoffAngle;
};

layout(binding = 0) uniform sampler2D textureSampler;
uniform Material material;

uniform int numPointLights;
uniform int numSpotLights;
uniform BaseLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

vec3 GouraudModel(vec3 eyePos, vec3 fromLightVector, vec3 normal, vec3 lightColor)
{
    vec3 color = vec3(0);

    //Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normal), 0);
    color += material.Kd * lightColor * diffuseFactor;
    
    // Specular
    if(diffuseFactor > 0)
    {
        vec3 reflectedLight = reflect(fromLightVector, normal);
        vec3 toCameraVector = normalize(- eyePos);
        float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
        specularFactor = pow(specularFactor, material.shineDamper);
        color += material.Ks * lightColor * material.reflectivity * specularFactor;
    }

    return color;
}

vec3 ComputeDirectionalLight(vec3 eyePos, vec3 normal, DirectionalLight directionalLight)
{
    vec3 fromLightVector = normalize(directionalLight.direction);
    vec3 color = GouraudModel(eyePos, fromLightVector, normal, directionalLight.baseLight.color) * directionalLight.baseLight.intensity;

    return color;
}

vec3 ComputePointLight(vec3 eyePos, vec3 normal, PointLight pointLight)
{
    vec3 fromLightVector = eyePos - pointLight.position;
    float d = length(fromLightVector);

    fromLightVector = normalize(fromLightVector);
    vec3 color = GouraudModel(eyePos, fromLightVector, normal, pointLight.baseLight.color) * pointLight.baseLight.intensity;

    float attenuation =  1.0f / (pointLight.constAtt + d * pointLight.linearAtt + d * d * pointLight.quadraticAtt);
    color *= attenuation;

    return color;
}

vec3 ComputeSpotLight(vec3 eyePos, vec3 normal, SpotLight spotLight)
{
    vec3 toFragmentVector = normalize(eyePos - spotLight.pointLight.position);
    float cosAngle = dot(spotLight.direction, toFragmentVector);

    vec3 color = vec3(0);

    if(cosAngle >= spotLight.cutoffAngle)
    {
        color = ComputePointLight(eyePos, normal, spotLight.pointLight);
        color *= (1.0 - (1.0 - cosAngle)/(1.0 - spotLight.cutoffAngle));
    }

    return color;
}

vec3 ComputeLighting(vec3 eyePos, vec3 normal)
{
    vec3 color = vec3(0);

    // Directional
    color += ComputeDirectionalLight(eyePos, normal, directionalLight);

    for(int i = 0; i < numPointLights; i++)
	{
        color += ComputePointLight(eyePos, normal, pointLights[i]);
	}

    for(int i = 0; i < numSpotLights; i++)
	{
        color += ComputeSpotLight(eyePos, normal, spotLights[i]);
	}

    // Ambiant
    color += material.Ka * ambientLight.color * ambientLight.intensity;

    return color;   
}

void main()
{
    vec4 eyePos = vec4(0);

    // Front face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Back face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Right face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Left face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();


    // Top face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Bottom face
    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(-0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * modelMatrix * (gs_in[0].relativePos + vec4(0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();
}
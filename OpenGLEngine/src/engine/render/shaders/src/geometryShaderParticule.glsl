#version 460

#define MAX_DIR_LIGHT 3
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 5

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

in VS_OUT {
    vec4 worldPos;
	float transp;
} gs_in[];

out GS_OUT
{
    float transp;
    vec3 color;
} gs_out;


/* Lights */
struct BaseLight
{
    vec3 color;
    float intensity;
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

uniform BaseLight ambientLight;
uniform DirectionalLight directionalLights[MAX_DIR_LIGHT];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


float shineDamper = 200;
float reflectivity = 1;
vec3 actualKa = vec3(0, 0.6f, 0.9f);
vec3 actualKd = vec3(0, 0.6f, 0.9f);
vec3 actualKs = vec3(1);

vec3 GouraudModel(vec3 eyePos, vec3 fromLightVector, vec3 normal, vec3 lightColor)
{
    vec3 color = vec3(0);

    //Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normal), 0);
    color += actualKd * lightColor * diffuseFactor;
    
    // Specular
    if(diffuseFactor > 0)
    {
        vec3 reflectedLight = reflect(fromLightVector, normal);
        vec3 toCameraVector = normalize(- eyePos);
        float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
        specularFactor = pow(specularFactor, shineDamper);
        color += actualKs * lightColor * reflectivity * specularFactor;
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
    for(int i = 0; i < MAX_DIR_LIGHT; i++)
	{
		if(directionalLights[i].baseLight.intensity <= 0)
			break;
        color += ComputeDirectionalLight(eyePos, normal, directionalLights[i]);
	}

    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if(pointLights[i].baseLight.intensity <= 0)
			break;
        color += ComputePointLight(eyePos, normal, pointLights[i]);
	}

    for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
        if(spotLights[i].pointLight.baseLight.intensity <= 0)
			break;
        color += ComputeSpotLight(eyePos, normal, spotLights[i]);
	}

    // Ambiant
    color += actualKa * ambientLight.color * ambientLight.intensity;

    return color;   
}

void main()
{
    vec4 eyePos = vec4(0);

    // Front face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, 1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Back face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 0, -1, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Right face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Left face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(-1, 0, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();


    // Top face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5, 0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, 0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, 1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();

    // Bottom face
    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5, -0.5f, -0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(-0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    eyePos = viewMatrix * (gs_in[0].worldPos + vec4(0.5f, -0.5f, 0.5f, 1));
    gs_out.transp = gs_in[0].transp;
    gs_out.color = ComputeLighting(eyePos.xyz, (viewMatrix * vec4(0, -1, 0, 0)).xyz);
    gl_Position = projectionMatrix * eyePos;
    EmitVertex();

    EndPrimitive();
}
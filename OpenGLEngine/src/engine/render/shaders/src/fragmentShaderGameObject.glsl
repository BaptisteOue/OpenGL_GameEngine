#version 460 core

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

in OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} fs_in;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 brightColor;

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


layout(binding = 0) uniform sampler2D materialTexture;
layout(binding = 1) uniform sampler2D shadowMap;

uniform Material material;

uniform int numPointLights;
uniform int numSpotLights;
uniform BaseLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];


vec3 actualKa;
vec3 actualKd;
vec3 actualKs;
vec4 actualNormal; // In eye space depending on gl_FrontFacing

vec3 phongModel(vec3 fromLightVector, vec3 lightColor)
{
    vec3 color = vec3(0);

    vec3 normalize_normal = normalize(actualNormal.xyz);

    // Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normalize_normal), 0);
    color += actualKd * lightColor * diffuseFactor;
    
    // Specular
    if(diffuseFactor > 0)
    {
        vec3 reflectedLight = reflect(fromLightVector, normalize_normal);
        vec3 toCameraVector = normalize(- fs_in.eye_pos.xyz);
        float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
        specularFactor = pow(specularFactor, material.shineDamper);
        color += actualKs * lightColor * material.reflectivity * specularFactor;
    }

    return color;
}

vec4 ComputeDirectionalLight(DirectionalLight directionalLight)
{
    vec3 fromLightVector = normalize(directionalLight.direction);
    vec3 color = phongModel(fromLightVector, directionalLight.baseLight.color) * directionalLight.baseLight.intensity;

    return vec4(color, 1);
}

vec4 ComputePointLight(PointLight pointLight)
{
    vec3 fromLightVector = fs_in.eye_pos.xyz - pointLight.position;
    float d = length(fromLightVector);

    fromLightVector = normalize(fromLightVector);
    vec3 color = phongModel(fromLightVector, pointLight.baseLight.color) * pointLight.baseLight.intensity;

    float attenuation =  1.0f / (pointLight.constAtt + d * pointLight.linearAtt + d * d * pointLight.quadraticAtt);
    color *= attenuation;

    return vec4(color, 1);
}

vec4 ComputeSpotLight(SpotLight spotLight)
{
    vec3 toFragmentVector = normalize(fs_in.eye_pos.xyz - spotLight.pointLight.position);
    float cosAngle = dot(spotLight.direction, toFragmentVector);

    vec4 color = vec4(0);

    if(cosAngle >= spotLight.cutoffAngle)
    {
        color = ComputePointLight(spotLight.pointLight);
        color *= (1.0 - (1.0 - cosAngle)/(1.0 - spotLight.cutoffAngle));
    }

    return color;
}

void SetUpMaterialColor()
{
    if(material.isTextured)
    {
        vec4 texColor = texture(materialTexture, fs_in.texCoords * 20);
        actualKa = texColor.rgb;
        actualKd = texColor.rgb;
    }
    else
    {
        actualKa = material.Ka;
        actualKd = material.Kd;
    }

    actualKs = material.Ks;
}

float shadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoord = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoord = (projCoord + 1) / 2;

    float currentDepth = projCoord.z;

    float bias = 0.001f;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    for(int u = -1; u <= 1; u++)
    {
        for(int v = -1; v <= 1; v++)
        {
            float pcfDepth = texture(shadowMap, projCoord.xy + vec2(u, v) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    return shadow;
}

void main()
{
    fragColor = vec4(0);



    if(gl_FrontFacing)
        actualNormal = fs_in.eye_normal;
    else
        actualNormal = -1 * fs_in.eye_normal;

    // Setup Ka, Kd, Ks if textured
    SetUpMaterialColor();

    fragColor += ComputeDirectionalLight(directionalLight);

    for(int i = 0; i < numPointLights; i++)
	{
        fragColor += ComputePointLight(pointLights[i]);
	}

    for(int i = 0; i < numSpotLights; i++)
	{
        fragColor += ComputeSpotLight(spotLights[i]);
	}

    // Add shadow
    if(directionalLight.baseLight.intensity > 0 && directionalLight.baseLight.castShadow)
    {
        float shadow = shadowCalculation(fs_in.fragPosLightSpace);         
        fragColor *= (1 - shadow);
    }

    // Add Ambient light
    fragColor += vec4(actualKa * ambientLight.color * ambientLight.intensity, 1);


    // Add brightColor for bloom pass
    float brightness = dot(fragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 10.0f)
        brightColor = vec4(fragColor.rgb, 1.0);
    else
        brightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
#version 460 core

#define MAX_DIR_LIGHT 3
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 5


in OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
    vec2 texCoords;
} fs_in;

out vec4 fragColor;

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


uniform Material material;
layout(binding = 0) uniform sampler2D textureSampler;

uniform DirectionalLight directionalLights[MAX_DIR_LIGHT];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];


vec3 actualKa;
vec3 actualKd;
vec3 actualKs;

vec3 phongModel(vec3 fromLightVector, vec3 lightColor)
{
    vec3 color = vec3(0);

    
    vec3 normalize_normal = normalize(fs_in.eye_normal.xyz);

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
    
    // Ambiant
    color += actualKa * lightColor;

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
        vec4 texColor = texture(textureSampler, fs_in.texCoords * 10);
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

void main()
{
    fragColor = vec4(0);

    // Setup Ka, Kd, Ks if textured
    SetUpMaterialColor();

    for(int i = 0; i < MAX_DIR_LIGHT; i++)
	{
		if(directionalLights[i].baseLight.intensity <= 0)
			break;
        fragColor += ComputeDirectionalLight(directionalLights[i]);
	}
        
    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if(pointLights[i].baseLight.intensity <= 0)
			break;
        fragColor += ComputePointLight(pointLights[i]);
	}

    for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
        if(spotLights[i].pointLight.baseLight.intensity <= 0)
			break;
        fragColor += ComputeSpotLight(spotLights[i]);
	}
 
}
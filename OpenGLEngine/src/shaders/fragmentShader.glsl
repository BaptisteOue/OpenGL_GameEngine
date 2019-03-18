#version 460 core

in OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
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
};

/* Lights */
struct DirectionalLight
{
    vec3 color;
    vec3 direction;
};

struct PointLight
{
    vec3 color;
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

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;


vec3 phongModel(vec3 fromLightVector, vec3 lightColor)
{
    vec3 color = vec3(0);

    
    vec3 normalize_normal = normalize(fs_in.eye_normal.xyz);

    // Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normalize_normal), 0);
    color += material.Kd * lightColor * diffuseFactor;
    
    // Specular
    if(diffuseFactor > 0)
    {
        vec3 reflectedLight = reflect(fromLightVector, normalize_normal);
        vec3 toCameraVector = normalize(- fs_in.eye_pos.xyz);
        float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
        specularFactor = pow(specularFactor, material.shineDamper);
        color += material.Ks * lightColor * material.reflectivity * specularFactor;
    }
    
    // Ambiant
    color += material.Ka * lightColor;

    return color;
}

vec4 ComputeDirectionalLight(DirectionalLight directionalLight)
{
    vec3 fromLightVector = normalize(directionalLight.direction);

    return vec4(phongModel(fromLightVector, directionalLight.color), 1);
}

vec4 ComputePointLight(PointLight pointLight)
{
    vec3 fromLightVector = fs_in.eye_pos.xyz - pointLight.position;
    float d = length(fromLightVector);

    fromLightVector = normalize(fromLightVector);
    vec3 color = phongModel(fromLightVector, pointLight.color);

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

void main()
{
    fragColor = ComputeDirectionalLight(directionalLight) + ComputePointLight(pointLight) + ComputeSpotLight(spotLight);
}
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

uniform Material material;
uniform DirectionalLight directionalLight;

vec3 phongModel()
{
    vec3 color = vec3(0);

    vec3 fromLightVector = normalize(directionalLight.direction);
    vec3 normalize_normal = normalize(fs_in.eye_normal.xyz);

    // Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normalize_normal), 0);
    color += material.Kd * directionalLight.color * diffuseFactor;
    
    // Specular
    if(diffuseFactor > 0)
    {
        vec3 reflectedLight = reflect(fromLightVector, normalize_normal);
        vec3 toCameraVector = normalize(- fs_in.eye_pos.xyz);
        float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
        specularFactor = pow(specularFactor, material.shineDamper);
        color += material.Ks * directionalLight.color * material.reflectivity * specularFactor;
    }
    
    // Ambiant
    color += material.Ka * directionalLight.color;

    return color;
}

void main()
{
    fragColor = vec4(phongModel(), 1);
}
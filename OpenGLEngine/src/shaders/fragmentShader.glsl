#version 460 core

in VS_OUT
{
    vec4 world_pos;
    vec4 world_normal;
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


uniform vec3 cameraPos;
uniform Material material;
uniform DirectionalLight directionalLight;

vec3 phongModel()
{
    vec3 color = vec3(0);

    vec3 fromLightVector = normalize(directionalLight.direction);
    vec3 normalize_normal = normalize(fs_in.world_normal.xyz);

    // Diffuse 
    float diffuseFactor = max(dot(-fromLightVector, normalize_normal), 0);
    color += material.Kd * directionalLight.color * diffuseFactor;
    
    // Specular
    vec3 reflectedLight = reflect(fromLightVector, normalize_normal);
    vec3 toCameraVector = normalize(cameraPos - fs_in.world_pos.xyz);
    float specularFactor = max(dot(reflectedLight, toCameraVector), 0);
    specularFactor = pow(specularFactor, material.shineDamper);
    color += color * material.Ks * directionalLight.color * material.reflectivity * specularFactor;
    
    // Ambiant
    color += material.Ka * directionalLight.color;

    return color;
}

void main()
{
    fragColor = vec4(phongModel(), 1);
}
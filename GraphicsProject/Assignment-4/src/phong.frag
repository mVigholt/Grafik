#version 330 core

uniform vec3 AmbientLightColor; // Ambient light intensity
uniform vec3 LightPosition;    // Position of the light source
uniform vec3 LightColor;       // Intensity/color of the light source

uniform vec3 EyePosition;      // Position of the camera/eye

uniform vec3 AmbientColor;     // Material ambient color
uniform vec3 DiffuseColor;     // Material diffuse color
uniform vec3 SpecularColor;    // Material specular color
uniform float Shininess;       // Material shininess coefficient

in vec3 WorldVertex;           // Position of the fragment in world space
in vec3 WorldNormal;           // Normal at the fragment in world space

out vec4 FragColor;            // Final output color

void main() {
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    // Implement your phong shader program here.
    //============================================================================
    // Normalize the normal vector
    vec3 N = normalize(WorldNormal);
    
    // Compute the vector from the fragment to the light source
    vec3 L = normalize(LightPosition - WorldVertex);
    
    // Compute the vector from the fragment to the eye/camera
    vec3 V = normalize(EyePosition - WorldVertex);
    
    // Compute the reflection vector
    vec3 R = reflect(-L, N);
    
    //----------------------------------------------------------------------------
    // Compute the ambient contribution
    vec3 ambient = AmbientLightColor * AmbientColor;
    
    //----------------------------------------------------------------------------
    // Compute the diffuse contribution (Lambert's cosine law)
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = LightColor * DiffuseColor * diff;
    
    //----------------------------------------------------------------------------
    // Compute the specular contribution (Phong reflection model)
    float spec = max(dot(V, R), 0.0);
    vec3 specular = (LightColor * SpecularColor) * pow(spec, Shininess);

    //----------------------------------------------------------------------------
    // Combine all components
    color = ambient + diffuse + specular;

    //============================================================================
    FragColor = vec4(color, 1.0f);
}
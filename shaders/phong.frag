#version 330 core

in vec3 wPos;     // Posición espacio mundo
in vec3 wNormal;  // Normal espacio mundo 
in vec2 texCoord; // Coords. textura

// Spotlight (linterna)
uniform vec3 slPos;             // Posición foco
uniform vec3 slDir;             // Dirección foco
uniform float slAmbient;        // Intensidad ambiental
uniform float slDiffuse;        // Intensidad difusa
uniform float slSpecular;       // Intensidad especular
uniform float inAngle;          // Ángulo interior
uniform float extAngle;         // Ángulo exterior
uniform vec3 camPos;            // Posición cámara
// Material
uniform sampler2D diffuseTex;   // Textura difusa
uniform float specularStrength; // Brillo especular

out vec4 fragColor; // Color final del píxel

void main()
{
    // Color base
    vec4 baseColor = texture(diffuseTex, texCoord);

    // 1. AMBIENTE
    vec3 ambient = slAmbient * baseColor.rgb;

    // 2. Calcular si el fragmento está dentro del foco
    // Vector de dirección del foco
    vec3 dirVector = normalize(slPos - wPos);
    // Coseno del ángulo
    float cosAngle = dot(dirVector, normalize(-slDir));

    // Si no está iluminado por la linterna
    vec3 final = ambient;

    // Si está iluminado por la linterna
    if (cosAngle > extAngle)
    {
        // 3. DIFUSA
        float diffuseFactor = max(dot(normalize(wNormal), dirVector), 0.0);
        vec3 diffuse = slDiffuse * diffuseFactor * baseColor.rgb;

        // 4. ESPECULAR
        vec3 refVector = reflect(-dirVector, normalize(wNormal));
        vec3 viewVector = normalize(camPos - wPos);
        float specularFactor = pow(max(dot(viewVector, refVector), 0.0), specularStrength);
        vec3 specular = vec3(slSpecular * specularFactor);

        // 5. ATENUACIÓN suave en los bordes del cono
        float coneFactor = smoothstep(extAngle, inAngle, cosAngle);

        // 6. ATENUACIÓN conforme incrementa la distancia viajada del rayo de luz
        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032;

        float distance = length(slPos - wPos);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance);

        // 6. FINAL
        final = ambient + coneFactor * attenuation * (diffuse + specular);
    }

    // Se establece el color final del píxel
    fragColor = vec4(final, 1.0);
}
// Hacemos una función para cargar texturas, como se recomendó en clase
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "bibliotecascurso/stb_image.h"
#include "textures.h"

// =========================
// PÚBLICAS
// =========================
// CARGAR TEXTURA
GLuint loadTexture(const char* path)
{
    // 1. Decir a stb_image que voltee las imágenes verticalmente
    // - Imágenes: origen (0, 0) -> esquina superior izquierda
    // - Coordenadas UV: origen (0, 0) -> esquina inferior izquierda
    // - Sin el flip aparecerían al revés
    stbi_set_flip_vertically_on_load(true);

    // 2. Generar y enlazar objeto de textura
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // 3. Cargar la imagen con stb_image
    // Ancho y alto de la imagen
    // Los canales: 3 o 4 (RGB o RGBA)
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    if (!data)
    {
        std::cerr << "Error al cargar la textura: " << path << ".\n";
        return 0;
    }

    // 4. Subir los datos a la GPU
    // - target: GL_TEXTURE_2D, se usan texturas 2D
    // - level: 0, es el nivel de detalle para mipmaps
    // - internalformat: definido por if de canales para decidir entre
    //                 - GL_RGB
    //                 - GL_RGBA
    // - width: variable local
    // - height: variable local
    // - border: siempre 0 obligatoriamente
    // - format: ídem internalformat
    // - type: GL_UNSIGNED_BYTE, el tipo de cada componente de color
    // - data: variable local
    if (channels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (channels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        std::cerr << "Formato de imagen no soportado: " << channels << " canales.\n";
    
    // 5. Configurar filtros y wrapping
    // - WRAP_S y WRAP_T controlan qué pasa si las UV salen del rango [0, 1]
    // - GL_REPEAT repite la textura
    // - MIN_FILTER y MAG_FILTER controlan el filtrado al escalar
    // - GL_LINEAR interpola entre texels vecinos
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 6. Liberar la memoria de la CPU
    stbi_image_free(data);

    // Devolver el ID
    return id;
}
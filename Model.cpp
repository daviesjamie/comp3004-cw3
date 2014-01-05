#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glimg/glimg.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <stdio.h>

#include "Model.hpp"
#include "utils/objloader.hpp"

Model::Model( string file )
{
    modelPath = file;
}

void Model::load()
{
    load_obj( modelPath, vertices, uvs, normals );

    glGenBuffers( 3, vbo );
    glGenVertexArrays( 1, vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec3 ), &vertices[ 0 ], GL_STATIC_DRAW );
    glBindVertexArray( vao[ 0 ] );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 1 ] );
    glBufferData( GL_ARRAY_BUFFER, uvs.size() * sizeof( glm::vec2 ), &uvs[ 0 ], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( glm::vec2 ), (const GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 2 ] );
    glBufferData( GL_ARRAY_BUFFER, normals.size() * sizeof( glm::vec3 ), &normals[ 0 ], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );
}

/*
 * Loads an image file of PNG, JPEG, TGA, BMP or GIF
 * into an OpenGL texture, and returns the texture ID.
*/
GLuint Model::load_texture( string textureFile )
{
    // Load image
    glimg::ImageSet** images = new glimg::ImageSet*[ 1 ];
    images[ 0 ] = glimg::loaders::stb::LoadFromFile( textureFile.c_str() );
    int width = images[ 0 ]->GetDimensions().width;
    int height = images[ 0 ]->GetDimensions().height;

    // Generate texture
    glEnable( GL_TEXTURE_2D );
    glGenTextures( 1, textureID );
    glBindTexture( GL_TEXTURE_2D, textureID[ 0 ] );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glPixelStorei( GL_UNPACK_ALIGNMENT, images[ 0 ]->GetFormat().LineAlign() );
    const glimg::SingleImage &img = images[ 0 ]->GetImage( 0, 0, 0 );
    const glimg::Dimensions &dim = img.GetDimensions();
    const glimg::OpenGLPixelTransferParams fmt = glimg::GetUploadFormatType( img.GetFormat(), 0 );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, dim.width, dim.height, 0, fmt.format, fmt.type, img.GetImageData() );
    glGenerateMipmap( GL_TEXTURE_2D );

    // Clean up
    delete images[ 0 ];
    delete[] images;
}

void Model::rotate( float amount, glm::vec3 axes )
{
    model = glm::rotate( model, amount, axes );
}

void Model::scale( glm::vec3 amounts )
{
    model = glm::scale( model, amounts );
}

void Model::translate( glm::vec3 amounts )
{
    model = glm::translate( model, amounts );
}

void Model::render()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBindTexture( GL_TEXTURE_2D, textureID[ 0 ] );
    glBindVertexArray( vao[ 0 ] );
    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glDrawArrays( GL_TRIANGLES, 0, vertices.size() );
}

glm::mat4 Model::get_model()
{
    return model;
}

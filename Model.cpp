#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glimg/glimg.h>
#include <memory>
#include <stdio.h>

#include "objloader.hpp"
#include "Model.hpp"

Model::Model( string file )
{
    path = file;
}

void Model::load()
{
    load_obj( path, vertices, uvs, normals );

    glGenBuffers( 3, vbo );
    glGenVertexArrays( 1, vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec3 ), &vertices[ 0 ], GL_STATIC_DRAW );
    glBindVertexArray( vao[ 0 ] );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 1 ] );
    glBufferData( GL_ARRAY_BUFFER, textures.size() * sizeof( glm::vec2 ), &textures[ 0 ], GL_STATIC_DRAW );
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
    glEnable( GL_TEXTURE_2D );
    glGenTextures( 1, textureID );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, textureID[ 0 ] );

    std::auto_ptr<glimg::ImageSet> imgset;

    try
    {
        imgset.reset( glimg::loaders::stb::LoadFromFile( textureFile ) );
        std::auto_ptr<glimg::Image> &img( imgset->GetImage( 0, 0, 0 ) );

        glimg::Dimensions &dims = img.GetDimensions();
        glimg::OpenGLPixelTransferParams fmt = glimg::GetUploadFormatType( img.GetFormat(), 0 );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, dims.width, dims.height, 0, fmt.format, fmt.type, img.GetImageData() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    catch( glimg::loaders::stb::StbLoaderException &e )
    {
        fprintf( stderr, e.what() );
        throw;
    }

    return textureID[ 0 ];
}

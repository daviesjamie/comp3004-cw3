#include <GL/glew.h>
#include <cstdio>
#include <vector>

#include "filetobuffer.hpp"
#include "shader.hpp"

GLint create_shader( const char* filename, GLenum type )
{
    const GLchar* source = file_to_buffer( filename );
    if( source == NULL )
    {
        fprintf( stderr, "Error opening %s: ", filename ); perror( "" );
        return 0;
    }

    GLuint res = glCreateShader( type );
    glShaderSource( res, 1, &source, NULL );
    free( (void*) source );

    glCompileShader( res );
    GLint compile_ok = GL_FALSE;
    glGetShaderiv( res, GL_COMPILE_STATUS, &compile_ok );
    if( compile_ok == GL_FALSE )
    {
        fprintf( stderr, "%s: ", filename );
        printLog( res );
        glDeleteShader( res );
        return 0;
    }

    return res;
}

// Creates a shader program from a vector of shader IDs
GLint link_shaders( const std::vector<GLint> &shaders )
{
    GLuint program = glCreateProgram();
    for( GLuint i = 0; i < shaders.size(); i++ )
        glAttachShader( program, shaders[ i ] );

    glLinkProgram( program );

    return program;
}

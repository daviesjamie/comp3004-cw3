#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "utils/filetobuffer.hpp"
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

void printLog( GLuint object )
{
    GLint log_length = 0;
    if( glIsShader( object ) )
        glGetShaderiv( object, GL_INFO_LOG_LENGTH, &log_length );
    else if( glIsProgram( object ) )
        glGetProgramiv( object, GL_INFO_LOG_LENGTH, &log_length );
    else
    {
        fprintf( stderr, "printlog: Not a shader or a program\n" );
        return;
    }

    char* log = ( char* )malloc( log_length );

    if( glIsShader( object ) )
        glGetShaderInfoLog( object, log_length, NULL, log );
    else if( glIsProgram( object ) )
        glGetProgramInfoLog( object, log_length, NULL, log );

    fprintf( stderr, "%s", log );
    free( log );
}

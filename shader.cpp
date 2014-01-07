// This code was largely adopted from
// http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_02

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <vector>

#include "utils/filetobuffer.hpp"
#include "shader.hpp"

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

GLint createShader( const char* filename, GLenum type )
{
    const GLchar* source = fileToBuffer( filename );
    if( source == NULL )
    {
        fprintf( stderr, "Error opening %s: ", filename ); perror( "" );
        return 0;
    }
    GLuint res = glCreateShader( type );
    glShaderSource( res, 1, &source, NULL );
    free( ( void* )source );

    glCompileShader( res );
    GLint compile_ok = GL_FALSE;
    glGetShaderiv( res, GL_COMPILE_STATUS, &compile_ok );
    if( compile_ok == GL_FALSE )
    {
        fprintf( stderr, "%s:", filename );
        printLog( res );
        glDeleteShader( res );
        return 0;
    }

    return res;
}

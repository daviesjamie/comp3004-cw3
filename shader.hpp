#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

GLint create_shader( const char* filename, GLenum type );
GLint link_shaders( const std::vector<GLint> &shaders );
void printLog( GLuint object );

#endif // SHADER_HPP_INCLUDED

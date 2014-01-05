#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

GLint create_shader( const char* filename, GLenum type );

GLint link_shaders( const std::vector<GLint> &shaders )

#endif // SHADER_HPP_INCLUDED

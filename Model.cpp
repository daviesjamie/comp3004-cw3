#include <GL/glew.h>

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

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
    model_path = file;
}

void Model::load()
{
    loadObj( model_path, vertices, normals );

    glGenBuffers( 3, vbo );
    glGenVertexArrays( 1, vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec3 ), &vertices[ 0 ], GL_STATIC_DRAW );
    glBindVertexArray( vao[ 0 ] );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 2 ] );
    glBufferData( GL_ARRAY_BUFFER, normals.size() * sizeof( glm::vec3 ), &normals[ 0 ], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );
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
    glBindVertexArray( vao[ 0 ] );
    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glDrawArrays( GL_TRIANGLES, 0, vertices.size() );
}

glm::mat4 Model::getModel()
{
    return model;
}

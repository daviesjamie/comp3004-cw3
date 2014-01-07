#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glimg/glimg.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <memory>
#include <stdio.h>

#include "Model.hpp"
#include "objloader.hpp"

Model::Model( string file )
{
    model_path = file;
    model = glm::mat4( 1.0f );
}

void Model::load()
{
    loadObj( model_path, vertices, normals );

    glGenBuffers( 2, vbo );
    glGenVertexArrays( 1, vao );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec3 ), &vertices[ 0 ], GL_STATIC_DRAW );
    glBindVertexArray( vao[ 0 ] );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 1 ] );
    glBufferData( GL_ARRAY_BUFFER, normals.size() * sizeof( glm::vec3 ), &normals[ 0 ], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), (const GLvoid*) 0 );
    glEnableVertexAttribArray( 1 );
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

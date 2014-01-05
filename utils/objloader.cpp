#include <cstdlib>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <stdio.h>
#include <string>

#include "common/objloader.hpp"

using namespace std;

/*
 * Splits a string on a given delimiter, and puts the parts
 * into the supplied elements vector.
*/
vector<string> &split( const string &str, char delimiter, vector<string> &elements )
{
    elements.clear();
    stringstream ss( str );
    string item;
    while( getline( ss, item, delimiter ) )
        elements.push_back( item );

    return elements;
}

/*
 * Splits a string on a given delimiter, and returns a
 * new vector containing the separate parts.
*/
vector<string> split( const string &str, char delimiter )
{
    vector<string> elements;
    split( str, delimiter, elements );
    return elements;
}

/*
 * A simple, rudimentary OBJ file loader. Returns true if successful.
 * Loads vertex, normal and texture coordinates from the file into the given vectors.
 * Adopted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading
*/
bool load_obj( const char* path, vector<glm::vec3> &vertices, vector<glm::vec2> &uvs, vector<glm::vec3> &normals )
{
    vector<glm::vec3> tempVertices;
    vector<glm::vec2> tempTextures;
    vector<glm::vec3> tempNormals;
    vector<unsigned int> vertIndices;
    vector<unsigned int> uvIndices;
    vector<unsigned int> normIndices;

    fstream file;
    file.open( path );

    if( file.is_open() )
    {
        // Stores the current line of the file
        string line;

        // Stores the parts of a line when splitting
        vector<string> parts;

        // Stores the parts of a face index when splitting
        vector<string> faceparts;

        while( file.good() )
        {
            getline( file, line );

            // Ignore Comment
            size_t match = line.find( "#", 0 );
            if( match != string::npos )
                continue;

            // Ignore materials
            match = line.find( "mtllib", 0 );
            if( match != string::npos )
                continue;
            match = line.find( "usemtl", 0 );
            if( match != string::npos )
                continue;

            // Ignore Object
            match = line.find( "o", 0 );
            if( match != string::npos )
                continue;

            // Texture Coordinates
            match = line.find( "vt", 0 );
            if( match != string::npos )
            {
                split( line, ' ', parts );
                double x = atof( parts[ 1 ].c_str() );
                double y = atof( parts[ 2 ].c_str() );
                tempTextures.push_back( glm::vec2( x, y ) ) );
                continue;
            }

            // Normal Coordinates
            match = line.find( "vn", 0 );
            if( match != string::npos )
            {
                split( line, ' ', parts );
                double x = atof( parts[ 1 ].c_str() );
                double y = atof( parts[ 2 ].c_str() );
                double z = atof( parts[ 3 ].c_str() );
                tempNormals.push_back( glm::vec3( x, y, z ) );
                continue;
            }

            // Vertex Coordinates
            match = line.find( "v", 0 );
            if( match != string::npos )
            {
                split( line, ' ', parts );
                double x = atof( parts[ 1 ].c_str() );
                double y = atof( parts[ 2 ].c_str() );
                double z = atof( parts[ 3 ].c_str() );
                tempVertices.push_back( glm::vec3( x, y, z ) );
                continue;
            }

            // Face Indices
            match = line.find( "f", 0 );
            if( match != string::npos )
            {
                split( line, ' ', parts );
                for( int i = 1; i < parts.size(); i++ )
                {
                    split( parts[ i ], '/', faceparts );

                    if( faceparts.size() != 3 )
                    {
                        stderr << "Invalid face declaration: " + parts[ i ];
                        return false;
                    }

                    vertIndices.push_back( atoi( faceparts[ 0 ].c_str() );
                    uvIndices.push_back( atoi( faceparts[ 1 ].c_str() );
                    normIndices.push_back( atoi( faceparts[ 2 ].c_str() );
                }
            }
            continue;
        }
    }

    for( int i = 0; i < vertIndices.size(); i++ )
    {
        int vertIndex = vertIndices[ i ];
        glm::vec3 vertex = tempVertices[ vertIndex - 1 ];
        vertices.push_back( vertex );

        int uvIndex = uvIndices[ i ];
        glm::vec3 uv = tempTextures[ uvIndex - 1 ];
        textures.push_back( uv );

        int normIndex = normIndices[ i ];
        glm::vec3 norm = tempNormals[ normIndex - 1 ];
        normals.push_back( norm );
    }

    return true;
}

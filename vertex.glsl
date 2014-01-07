#version 330 core

// Input vertex data
layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec3 normal;

// The (constant) MVP matrix
uniform mat4 mvp;

uniform bool enable_shading;
uniform vec3 light_color;
uniform vec3 light_direction;
uniform vec3 object_color;
uniform float ambient_intensity;

//const bool enable_shading = true;
//const vec3 object_color = vec3( 1.0f, 1.0f, 1.0f );
//const vec3 light_color = vec3( 0.5f, 0.5f, 0.5f );
//const vec3 light_direction = -vec3( 0.0f, 0.0f, -10.0f ); // Opposite of camera position
//const float ambient_intensity = 0.1f;

// The variables to pass along the chain
out VertexData {
    vec4 position;
    vec3 color;
    vec3 normal;
} VertexOut;

void main()
{
    // Output position of the vertex
    gl_Position = mvp * position;

    // Position of the vertex (to pass to the geometry shader)
    VertexOut.position = position;

    // Output color of the vertex
    if( enable_shading )
    {
        vec3 mvp_normal = ( mvp * vec4( normal, 0.0f ) ).xyz;
        float diffuse_intensity = max( 0.0f, dot( normalize( mvp_normal ), normalize( -light_direction ) ) );
        VertexOut.color = object_color * ( light_color * min( 1.0f, ambient_intensity + diffuse_intensity ) );
    }
    else
    {
        VertexOut.color = object_color;
    }

    // Normal of the vertex
    VertexOut.normal = normal;
}

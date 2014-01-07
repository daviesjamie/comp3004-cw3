#version 330 core

// Input data
in VertexData {
    vec3 color;
    vec4 normal;
} VertexIn;

// Output data
out vec3 color;

void main()
{
    // Output color of the fragment
    color = VertexIn.color;
}

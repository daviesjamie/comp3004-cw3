#version 330 core

// Based upon the 'Normal Interpolated Shading' from:
// https://secure.ecs.soton.ac.uk/notes/comp3004/Shading.Object.php

layout( location = 0 ) in vec3 in_position;
layout( location = 1 ) in vec3 in_normal;

out vec4 ex_normal;

uniform mat4 mvp;

void main()
{
    vec4 v = vec4( in_position, 1 );
    gl_Position = mvp * v;
    ex_normal = vec4( in_normal, 0 );
}

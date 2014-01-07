#version 330 core

// Based upon the 'Normal Interpolated Shading' from:
// https://secure.ecs.soton.ac.uk/notes/comp3004/Shading.Object.php

precision highp float;

in vec4 ex_normal;

out vec4 gl_FragColor;

uniform vec4 light_position;
uniform vec4 light_color;
uniform vec4 object_color;

void main()
{
    gl_FragColor = object_color * light_color * dot( light_position, ex_normal );
}

#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 in_color;

out vec3 color;

uniform mat4 camera_matrix;

void main()
{
    gl_Position = camera_matrix * vec4(pos, 1.0);
    color = in_color;
}

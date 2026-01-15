#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 modelview;
uniform float vertex_size;

void main(void) {
  gl_Position = projection * modelview * vec4(position, 1.0);
  gl_PointSize = 1.0 * vertex_size;
}

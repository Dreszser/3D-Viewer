#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in float edge_progress;
layout(location = 2) in float edge_length;

out float g_progress;
out float g_length;

uniform mat4 projection;
uniform mat4 modelview;

void main() {
  gl_Position = projection * modelview * vec4(position, 1.0);

  g_progress = edge_progress;
  g_length = edge_length;
}

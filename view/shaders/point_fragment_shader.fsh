#version 330 core

uniform vec3 vertex_color;
uniform int vertex_type;
uniform float vertex_size;

out vec4 FragColor;

void main(void) {
  bool is_visible = !(vertex_size == 0.0 || vertex_type == 4);

  if (is_visible) {
    if (vertex_type == 5) {
      vec2 coord = gl_PointCoord - vec2(0.5);
      float distance = length(coord);

      if (distance > 0.5) {
        discard;
      }
    }
  } else {
    discard;
  }
  FragColor = vec4(vertex_color, 1.0);
}

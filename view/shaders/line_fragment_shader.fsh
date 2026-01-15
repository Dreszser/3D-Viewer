#version 330 core

in float f_progress;
in float f_length;

out vec4 FragColor;

uniform vec3 edge_color;
uniform float dash_length;

void main() {
  if (dash_length != 0.0) {
    float dash_count = f_length / dash_length;
    if (dash_count < 5.0) {
      dash_count = 5.0;
    }
    float pattern = mod(f_progress * dash_count, 1.0);

    if (pattern > 0.5) {
      discard;
    }
  }

  FragColor = vec4(edge_color, 1.0);
}

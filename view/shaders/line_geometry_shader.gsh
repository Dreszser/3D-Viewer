#version 330 core

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

in float g_progress[];
in float g_length[];

out float f_progress;
out float f_length;

uniform vec2 view_size;
uniform float edge_thickness;

void main() {
  vec4 p0 = gl_in[0].gl_Position;
  vec4 p1 = gl_in[1].gl_Position;

  // NDC - normalised device ccordinates
  vec2 ndc0 = p0.xy / p0.w;
  vec2 ndc1 = p1.xy / p1.w;

  vec2 direction = normalize(ndc1 - ndc0);
  vec2 normal = vec2(-direction.y, direction.x);

  vec2 pixel_size = 2.0 / view_size;

  vec2 offset = normal * pixel_size * edge_thickness * 0.5;

  vec2 v0 = ndc0 + offset;
  vec2 v1 = ndc0 - offset;
  vec2 v2 = ndc1 + offset;
  vec2 v3 = ndc1 - offset;

  // float w0 = p0.w;
  // float w1 = p1.w;

  gl_Position = vec4(v0 * p0.w, p0.z, p0.w);
  f_progress = g_progress[0];
  f_length = g_length[0];
  EmitVertex();

  gl_Position = vec4(v1 * p0.w, p0.z, p0.w);
  f_progress = g_progress[0];
  f_length = g_length[0];
  EmitVertex();

  gl_Position = vec4(v2 * p1.w, p1.z, p1.w);
  f_progress = g_progress[1];
  f_length = g_length[1];
  EmitVertex();

  gl_Position = vec4(v3 * p1.w, p1.z, p1.w);
  f_progress = g_progress[1];
  f_length = g_length[1];
  EmitVertex();

  EndPrimitive();
}

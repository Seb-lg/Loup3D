#version 430
uniform vec2 screenSize;
layout (local_size_x = 1, local_size_y = 1) in;
layout (rgba32f, binding = 0) uniform image2D img_output;

void main () {
  vec4 pixel;
  ivec2 pixel_coords = ivec2 (gl_GlobalInvocationID.xy);

  pixel = vec4 (1- (pixel_coords.y + 1.0)/screenSize.y, (pixel_coords.x + 1.0)/screenSize.x, (pixel_coords.y + 1.0)/screenSize.y, 1.);
  imageStore (img_output, pixel_coords, pixel);
}
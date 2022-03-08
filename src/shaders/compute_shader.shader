#version 430
uniform vec2 screenSize;
layout (local_size_x = 1, local_size_y = 1) in;
layout (rgba32f, binding = 0) uniform image2D img_output;

uint hash(uint state)
{
  state ^= 2747636419u;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  state ^= state >> 16;
  state *= 2654435769u;
  return state;
}

void main () {
  vec4 pixel;
  ivec2 pixel_coords = ivec2 (gl_GlobalInvocationID.xy);

  uint rd_int = hash(pixel_coords.x * pixel_coords.y);
  float val_out;
  float oui = fract(float(rd_int)/1000000.);
  pixel = vec4 (1- (pixel_coords.y + 1.0)/screenSize.y, (pixel_coords.x + 1.0)/screenSize.x, oui, oui);
  imageStore (img_output, pixel_coords, pixel);
}
#version 430
uniform vec2 screenSize;
uniform vec2 playerPos;
uniform vec2 mapSize;
uniform float angle;
uniform int map[10000];
layout (local_size_x = 1, local_size_y = 1) in;
layout (rgba32f, binding = 0) uniform image2D img_output;
float M_PIf = 3.14159265358979;

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

float SIGN(float a, float b) {
    if (a < 0 && b > 0)
        return -a;
    else if (a > 0 && b < 0)
        return -a;
    else return a;
}

vec4 raycast(int x, int y) {
    vec2 rayPos;
    vec2 vRayDir;
    vec2 vStep;
    vec2 rayHypot;
    vec2 rayAdd;
    float _angle;

    _angle = angle < 0 ? angle + 360.f : angle > 360.f ? angle - 360.f : angle;
    _angle = _angle - (90. / 2) + ((90. / screenSize.x) * x);
    rayPos.x = playerPos.x;
    rayPos.y = playerPos.y;
    vRayDir.x = cos(_angle * (M_PIf / 180.f));
    vRayDir.y = sin(_angle * (M_PIf / 180.f));
    float editMinimal = 0.00001;
    bool bTileFound = false;

    vStep.x = vRayDir.x < 0.f ? -1 : 1;
    vStep.y = vRayDir.y < 0.f ? -1 : 1;

    while (!bTileFound) {
        if (vStep.x == 1) { // CAH
            rayAdd.x = 1.f - (rayPos.x - float(floor(rayPos.x)));
            rayHypot.x = rayAdd.x / vRayDir.x;
        } else {
            rayAdd.x = rayPos.x - float(floor(rayPos.x));
            rayHypot.x = rayAdd.x / vRayDir.x;
        }

        if (vStep.y == 1) { // SOH
            rayAdd.y = 1.f - (rayPos.y - float(floor(rayPos.y)));
            rayHypot.y = rayAdd.y / vRayDir.y;
        } else {
            rayAdd.y = rayPos.y - float(floor(rayPos.y));
            rayHypot.y = rayAdd.y / vRayDir.y;
        }
        // Choose the smallest hypotenuse and increment other dimension
        if (abs(rayHypot.x) < abs(rayHypot.y)) {
            rayPos.x += SIGN(rayAdd.x, vStep.x) + editMinimal * vStep.x;
            rayPos.y += SIGN(vRayDir.y * rayHypot.x, vStep.y);
        } else {
            rayPos.y += SIGN(rayAdd.y, vStep.y) + editMinimal * vStep.y;
            rayPos.x += SIGN(vRayDir.x * rayHypot.y, vStep.x);
        }

        // Look on the map if the new position is a wall
        if (rayPos.x >= 0 && rayPos.x < mapSize.x && rayPos.y >= 0 && rayPos.y < mapSize.y) {
            if (map[int(rayPos.x) + int(rayPos.y) * int(mapSize.x)] == 1) {
                bTileFound = true;
            }
        } else {
            bTileFound = true;
        }
    }
    bool hitDirection = abs(rayHypot.x) < abs(rayHypot.y);
    //    exit(0);
    float distance = sqrt((pow(rayPos.x - playerPos.x, 2) + pow(rayPos.y - playerPos.y, 2.f)));
    int type = map[int(rayPos.x) + int(rayPos.y) * int(mapSize.x)];
    float hitpoint;
    if (hitDirection)
        hitpoint = rayPos.y - float(floor(rayPos.y));
    else
        hitpoint = rayPos.x - float(floor(rayPos.x));

    distance = distance * cos((angle - _angle) * (M_PIf / 180.0));
    distance = screenSize.y / distance;

    if (abs(y - screenSize.y / 2) > distance / 2)
        return vec4(1,1,0,1);
    else return vec4(0,0,0,1);

}


void main () {
    vec4 pixel;
    ivec2 pixel_coords = ivec2 (gl_GlobalInvocationID.xy);

    uint rd_int = hash(pixel_coords.x * pixel_coords.y);
    float val_out;
    float oui = fract(float(rd_int)/1000000.);
    pixel = raycast(pixel_coords.x , pixel_coords.y);
//    pixel = vec4 (1- (pixel_coords.y + 1.0)/screenSize.y, (pixel_coords.x + 1.0)/screenSize.x, oui, oui);
    imageStore (img_output, pixel_coords, pixel);
}
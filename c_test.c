#include <stdint.h>
#include <math.h>

#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define CHANNEL_NUM 3

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

int main() {
    int width = 0, height = 0, bpp = 0;

    uint8_t* rgb_image = stbi_load("red_circle.png", &width, &height, &bpp, 3);

    // int width = 800; 
    // int height = 800;

    // uint8_t * rgb_image;
    // rgb_image = malloc(width * height * CHANNEL_NUM);

    // Write your code to populate rgb_image here

    stbi_write_png("image.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    stbi_image_free(rgb_image);

    return 0;
}
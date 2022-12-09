#include <stdint.h>
#include <math.h>

#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define CHANNEL_NUM 3

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

struct LED {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} LED_t;

#define LEDS_PER_STRIP (40)
#define SLICES_ON_WHEEL (72)
#define WHEEL_DIAMETER (60)
#define HUB_DIAMETER (6.5)
#define WIDTH (225)
#define HEIGHT (225)

// 40 LEDs per strip length, 72 slices for every strip
struct LED returnValue[SLICES_ON_WHEEL][LEDS_PER_STRIP];
//struct LED image[HEIGHT][WIDTH];

int main() {
    int width = 0, height = 0, channels = 0;

    uint8_t *rgb_image = stbi_load("red_circle.png", &width, &height, &channels, 3);
    struct LED * image[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        image[i] = malloc(sizeof(struct LED) * WIDTH);
        memset(image[i], 0, sizeof(struct LED) * WIDTH);
    }
//    memset(image, 0, sizeof(struct LED[HEIGHT][WIDTH]));
    uint8_t red_pixel, green_pixel, blue_pixel;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            red_pixel = *(rgb_image + (i * (3 * width)) + (3 * j) + 0); // red
            green_pixel = *(rgb_image + (i * (3 * width)) + (3 * j) + 1); // green
            blue_pixel = *(rgb_image + (i * (3 * width)) + (3 * j) + 2); // blue

//            printf("Row: %d Column: %d red pixel: %d blue pixel: %d green pixel %d\n", i, j, red_pixel, blue_pixel, green_pixel);
            image[i][j].green = green_pixel;
            image[i][j].red = red_pixel;
            image[i][j].blue = blue_pixel;
        }
    }

    // int width = 800;
    // int height = 800;

    // uint8_t * rgb_image;
    // rgb_image = malloc(width * height * CHANNEL_NUM);

    // Write your code to populate rgb_image here

    stbi_write_png("image.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    stbi_image_free(rgb_image);
    for (int i = 0; i < HEIGHT; i++) {
        free(image[i]);
//        image[i] = malloc(sizeof(struct LED) * WIDTH);
    }
    return 0;
}
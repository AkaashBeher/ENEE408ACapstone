#include <stdint.h>
#include <stdio.h>
#include <math.h>

// Required #defines to use stb libraries
#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define CHANNEL_NUM 3

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"

// LED structure
struct LED {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} LED_t;

// #defines for constants of the design and wheel
#define LEDS_PER_STRIP (40)
#define SLICES_ON_WHEEL (10)
#define WHEEL_DIAMETER (60)
#define HUB_DIAMETER (6.5)
//#define WHEEL_DIAMETER (5.0)
//#define HUB_DIAMETER (1.0)
#define PI 3.1415926535

// This function gets and prints the r,g,b pixel values for the specified pixel defined at y = height_loc, x = width_loc
// for the rgb_image passed in, in addition to passing in the total width of the image
void pixel_index_lookup(FILE *out_file, int height_loc, int width_loc, uint8_t * rgb_image, int image_width) {
    uint8_t red_pixel, green_pixel, blue_pixel;

    red_pixel = *(rgb_image + (height_loc * (3 * image_width)) + (3 * width_loc) + 0); // red
    green_pixel = *(rgb_image + (height_loc * (3 * image_width)) + (3 * width_loc) + 1); // green
    blue_pixel = *(rgb_image + (height_loc * (3 * image_width)) + (3 * width_loc) + 2); // blue

    fprintf(out_file, "{%d,%d,%d},", red_pixel, green_pixel, blue_pixel);
}


int main() {
    int width = 0, height = 0, channels = 0;

    // Load in the image
    uint8_t *rgb_image = stbi_load("hi.png", &width, &height, &channels, 3);
    
    // Force a square crop
    if (width < height) {
        height = width;
    } else {
        width = height;
    }
    
    FILE *out_file = fopen("output.txt", "w");

    fprintf(out_file, "width %d\n", width);
    fprintf(out_file, "height %d\n", height);

    int x_center = width - (width/2);
    int y_center = height - (height/2);


    int hubPixelOffset = (HUB_DIAMETER / WHEEL_DIAMETER) * (height/2); // Offset from center of wheel to edge of hub in pixels
    int pixelsBtwHubAndEdge = (height / 2) - hubPixelOffset; // # of pixels between edge of hub and edge of wheel

    for (int currentSlice = 0; currentSlice < SLICES_ON_WHEEL; currentSlice++) {
        // Calculate the angle for the LED pixel
        fprintf(out_file, "\n");
        int angle = (int) ((360.0 * (((double) currentSlice) / SLICES_ON_WHEEL) + 90.0)) % 360;
        // printf("angle %d\n", angle);
        for (int currentLED = 0; currentLED < LEDS_PER_STRIP; currentLED++) {
            // Step 1. Find the location of the pixel

            // Calculate the radius for the LED pixel
            int radius = hubPixelOffset + ((currentLED / (LEDS_PER_STRIP - 1.0)) * pixelsBtwHubAndEdge); // Number of sections between LEDs is 1 less than LEDS_PER_STRIP
            // if (currentSlice == 0) printf("radius %d\n", radius);

            // Given the radius and angle, figure out the x coordinate relative to the center
            int x = radius * (cos(angle * (PI/180)));

            // Given the radius and angle, figure out the y coordinate relative to the center
            int y = radius * (sin(angle* (PI/180)));

            // Convert the calculated x and y coordinates in terms of the top left of the image
            int convertedX = x + width/2;
            int convertedY = y + height/2;

            // Step 2. Grab and print the pixel
            pixel_index_lookup(out_file, convertedX, convertedY, rgb_image, width);
        }
    }


    stbi_write_png("image.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);
    stbi_image_free(rgb_image);

    fclose(out_file);

    return 0;
}
#include <stdio.h>
#include "libs.h"
#include <math.h>

#define pi 3.1415926535

#define HEIGHT 1000
#define WIDTH HEIGHT

#define DEGS 36

int main(int argc, char **argv) {
    int rad2 = HEIGHT*3/8;
    int rad1 = HEIGHT*2/8;
    int rad0 = HEIGHT*1/8;

    u_int8_t* rgb_image;
    rgb_image = malloc(WIDTH*HEIGHT*3);

    // Initialize to 0 (black)
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int color = 0; color < 3; color++) {
                rgb_image[x*HEIGHT*3 + y*3 + color] = 0xFF;
            }
        }
    }
    
    int x_cen;
    int y_cen;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            for (int color = 0; color < 3; color++) {
                x_cen = x-(WIDTH/2);
                y_cen = y-(HEIGHT/2);
                int mult = (x_cen > 0) ^ (y_cen > 0);
                mult = (mult * 2) - 1;
                
                int rad_sqrd = abs(x_cen)*abs(x_cen) + abs(y_cen)*abs(y_cen);
                if (rad_sqrd <= rad2*rad2 && rad_sqrd > rad1*rad1) {
                    if ((abs((int) (atan(((float)y_cen) / ((float)x_cen))*180/pi))+DEGS/4)%DEGS <= DEGS/2) {
                        rgb_image[y*WIDTH*3 + x*3 + color] = 0;
                    }   
                // } else if (rad_sqrd <= rad1*rad1 && rad_sqrd > rad0*rad0) {
                    // if ((abs((int) (atan(((float)y_cen) / ((float)x_cen))*180/pi))+(DEGS*1/4)+(DEGS*1/4*mult))%DEGS <= DEGS/2) {
                    //     rgb_image[y*WIDTH*3 + x*3 + color] = 0;
                    // }
                } else if (rad_sqrd <= 10) {
                    rgb_image[y*WIDTH*3 + x*3 + color] = 0;
                }
            }
        }
    }

    // Write your code to populate rgb_image here

    stbi_write_png("image.png", WIDTH, HEIGHT, 3, rgb_image, WIDTH*3);

    return 0;
}
#include <iostream>

using namespace cv;
using namespace std;

 struct LED {      
   uint8_t green;
   uint8_t red;
   uint8_t blue;         
 } LED_t;

 #define LEDS_PER_STRIP (40)
 #define SLICES_ON_WHEEL (72)
 #define WHEEL_DIAMETER (60)
 #define HUB_DIAMETER (6.5)

// 40 LEDs per strip length, 72 slices for every strip
static LED returnValue[SLICES_ON_WHEEL][LEDS_PER_STRIP];

int main() {

    // Calculate the number of LEDs for the entire length of the wheel
    int totalLEDLength = (LEDS_PER_STRIP * WHEEL_DIAMETER)/ ((WHEEL_DIAMETER - HUB_DIAMETER) / 2);
    
    Mat image = imread("C:\Users\akaas\Downloads\red_circle.png", IMREAD_grayscale); 

    // Image path "C:\Users\akaas\Downloads\red_circle.png"
    // std::cout << "Total LED Length " << totalLEDLength <<  "\n";
    // Output is 89, so 9 pixels of empty space 

    // Resize image to dimensions of 89 pixels to 89 pixels


    // // Initial image processing

    // // Gettting an image to the correct dimensions

    //

    // // For all of the slices to compute
    // for (int i = 0; i < SLICES_ON_WHEEL; i++) {
    //     // For each of the LEDs on that slice 
    //     for (int j = 0; j < LEDS_PER_STRIP; j++) {

    //         cout<<returnValue[i][j].green<<" ";

    //     }
    //     cout<<"New Line! \n"<<" ";
    // }

    // // Print members of myStructure
    // // std::cout << myStructure.myNum << "\n";
    // // std::cout << myStructure.myString << "\n";

    return 0;
}
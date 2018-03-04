#include <Arduino.h>

/*
 * Program: 4x4x4 LED Cube
 * Date: 07-August-2015 
 * 
 * xy-plane:
 * x = vertical
 * y = horizontal
 * Top view (positions):        Pin allocation:
 *   | 0 1 2 3                    | 0       1       2       3
 * --|--------                  --|-------------------------------
 *  0| o o o o                   0| 0       1       2       3
 *  1| o o o o                   1| 4       5       6       7
 *  2| o o o o                   2| 8       9       10      11
 *  3| o o o o                   3| 12      13      14(A0)  15(A1)
 * 
 * z-axis:
 * Side view (layers):          Pin allocation:
 * -----------                  ---------------
 *  3| o o o o                   3| 19(A5)
 *  2| o o o o                   2| 18(A4)
 *  1| o o o o                   1| 17(A3)
 *  0| o o o o                   0| 16(A2)
 *  
 */
byte xy[4][4];  // Declaring array to store LED positions correspond to pin number
byte z[4];      // Declaring array to store LED layers correspond to pin number
int i, j;       // Indices used in for loop

// Clear all led
void cubeClear()
{
    for(byte i = 0; i < 4; i++)
    {
        for(byte j = 0; j < 4; j++)
        {
            digitalWrite(xy[i][j], LOW);// Set all LED position pin to LOW
        }
        digitalWrite(z[i], HIGH);       // Set all LED layer pin to HIGH
    }
}

// On all led
void cubeON()
{
    for(byte i = 0; i < 4; i++)
    {
        for(byte j=0;j<4;j++)
        {
            digitalWrite(xy[i][j], HIGH);// Set all LED position pin to HIGH
        }
        digitalWrite(z[i], LOW);        // Set all LED layer pin to LOW
    }
}

// On one desired led
void ledON(byte xy, byte z)
{
    digitalWrite(xy, HIGH); // Set the desired LED position pin to HIGH
    digitalWrite(z, LOW);   // Set the desired LED layer pin to LOW
}

// Off one desired led
void ledOFF(byte xy, byte z)
{
    digitalWrite(xy, LOW);  // Set the desired LED position pin to LOW
    digitalWrite(z, HIGH);  // Set the desired LED layer pin to HIGH
}
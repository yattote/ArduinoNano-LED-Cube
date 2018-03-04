#include <main.h>


void setup()
{
    // Allocating the pin number to array xy
    byte pin = 0;

    // Store from pin 0 to 15
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            xy[i][j] = pin++;           // Store and increment to next pin number
            pinMode(xy[i][j], OUTPUT);  // Also set the pin as output
        }
    }

    // Allocate layers to array z
    // Continue to store pin starting from 16
    for(i = 0; i < 4; i++)
    {
        z[i] = pin++;
        pinMode(z[i], OUTPUT);
    }
    cubeClear();    // Clear the cube
}

void loop()
{
    // First line, blink and moving upward
    for(i = 0; i <= 3; i++)
    {
        ledOFF(xy[0][0], z[0]);
        delay(500);
        ledON(xy[0][0], z[0]);
        delay(500);
    }
    delay(1000);
    for(i = 1; i < 4; i++)
    {
        ledON(xy[0][0], z[i]);
        delay(50);
    }
    for(i = 0; i <= 2; i++)
    {
        digitalWrite(z[i], HIGH);
        delay(50);
    }
    delay(200);

    // Second line, moving downward
    ledON(xy[0][1],z[3]);
    delay(100);
    digitalWrite(xy[0][0],LOW);
    delay(250);
    for(i = 2; i >= 0; i--)
    {
        ledON(xy[0][1], z[i]);
        delay(50);
    }
    for(i = 3; i >= 1; i--)
    {
        digitalWrite(z[i], HIGH);
        delay(50);
    }
    delay(200);

    // Third line, moving horizontal
    ledON(xy[1][1], z[0]);
    delay(100);
    digitalWrite(xy[0][1], LOW);
    delay(250);
    ledON(xy[2][1], z[0]);
    delay(100);
    digitalWrite(xy[1][1], LOW);
    delay(250);
    ledON(xy[3][1], z[0]);
    delay(100);
    digitalWrite(xy[2][1], LOW);
    delay(250);

    // Fourth line, moving upward line by line
    for(i=0;i<4;i++)
    {
        ledON(xy[3][1],z[i]);
        delay(100);
    }
    cubeClear();
    delay(100);
    for(i=0;i<4;i++)
    {
        ledON(xy[2][1],z[i]);
        delay(100);
    }
    cubeClear();
    delay(100);
    for(i=0;i<4;i++)
    {
        ledON(xy[1][1],z[i]);
        delay(100);
    }
    cubeClear();
    delay(100);
    for(i=0;i<4;i++)
    {
        ledON(xy[0][1],z[i]);
        delay(100);
    }
    delay(1000);

    // Plane, create a vertical plane
    cubeClear();
    delay(500);
    for(i=0;i<4;i++)
    {
        digitalWrite(xy[i][1],HIGH);
    }
    for(i=0;i<=4;i++)
    {
        digitalWrite(z[i],LOW);
        delay(50);
    }
    delay(1000);

    // Layer0, light up LED one by one
    cubeClear();
    delay(500);
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            ledON(xy[i][j],z[0]);
            delay(100);
        }
    }
    delay(1000);

    // Layer 1, light up LED in a spiral shape
    cubeClear();
    delay(500);
    for(i=0;i<4;i++)
    {
        ledON(xy[0][i],z[1]);
        delay(50);
    }
    for(i=1;i<4;i++)
    {
        ledON(xy[i][3],z[1]);
        delay(50);
    }
    for(int i=2;i>=0;i--)
    {
        ledON(xy[3][i],z[1]);
        delay(50);
    }
    ledON(xy[2][0],z[1]);
    delay(50);
    for(i=0;i<=2;i++)
    {
        ledON(xy[1][i],z[1]);
        delay(50);
    }
    ledON(xy[2][2],z[1]);
    delay(50);
    ledON(xy[2][1],z[1]);
    delay(1000);

    // Layer2, light up LED as a claw shape
    cubeClear();
    delay(500);
    ledON(xy[0][3],z[2]);
    delay(100);
    ledON(xy[0][1],z[2]);
    ledON(xy[1][2],z[2]);
    ledON(xy[2][3],z[2]);
    delay(100);
    ledON(xy[1][0],z[2]);
    ledON(xy[2][1],z[2]);
    ledON(xy[3][2],z[2]);
    delay(100);
    ledON(xy[3][0],z[2]);
    delay(1000);

    // Layer3, light up all LED layer by layer
    cubeClear();
    delay(500);
    for(byte k=0;k<3;k++)
    {  
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                ledON(xy[i][j],z[3]);
            }
        }
        delay(100);
        for(i=2;i>=0;i--)
        {
            digitalWrite(z[i],LOW);
            delay(100);
        }
        for(i=3;i>=0;i--)
        {
            digitalWrite(z[i],HIGH);
            delay(100);
        }
        for(i=0;i<=3;i++)
        {
            digitalWrite(z[i],LOW);
            delay(100);
        }
        for(i=0;i<=3;i++)
        {
            digitalWrite(z[i],HIGH);
            delay(100);
        }
    }

    // Light up all LED and stay forever
    cubeClear();
    delay(500);
    cubeON();
    //while(1);
}
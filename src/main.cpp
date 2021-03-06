#include <main.h>

#ifdef DIM_3x3x3
/* xy-plane, Pin allocation:
 -|-------------------
 2| 12      11      10
 1| 9       8       7
 0| 6       5       4
 -|-------------------
 * z-axis (layers), Pin allocation:
-|---------
2| 14(A0)
1| 15(A1)
0| 16(A2)
-|--------- */
const int DIMENSIONS = 3;
const int PLANE_XY[9] = { 4, 5, 6, 7, 8, 9, 10, 11, 12 };
const int PLANE_Z[3] = { 14, 15, 16 };
#elif DIM_4x4x4
/* xy-plane, Pin allocation:
 -|-------------------------------
 3| 12      13      14(A0)  15(A1)
 2| 8       9       10      11
 1| 4       5       6       7
 0| 0       1       2       3
 -|-------------------------------
 * z-axis (layers), Pin allocation:
-|-------------
3| 16(A2)
2| 17(A3)
1| 18(A4)
0| 19(A5)
-|------------- */
const int DIMENSIONS = 4;
const int PLANE_XY[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const int PLANE_Z[4] = { 16, 17, 18, 19 };
#endif

#ifdef GAME
#include <CLedGame.h>

const EOrientation JOYSTICK_ORIENTATION = EOrientation::Orientation270;
CLedGame* m_Game;

void setup()
{
#ifdef DEBUG
    //init HardwareSerial to monitor and debug Arduino RX / TX and its activity
    Serial.begin(9600);
    Serial.println("Debugging LC-Game");
#endif
    m_Game = new CLedGame(DIMENSIONS, PLANE_XY, PLANE_Z, JOYSTICK_ORIENTATION);
}

void loop()
{
    m_Game->StartGame();
}
#endif

#if defined(CUBE_STARS) || defined(CUBE_RANDOM) || defined(CUBE_COMPLETE)
#include <CLedMarquee.h>

CLedMarquee* m_leds;

void setup()
{
    m_leds = new CLedMarquee(DIMENSIONS, PLANE_XY, PLANE_Z);
}

void loop()
{
    //
    m_leds->SetLedMarquee(TestAll);
    Common.Sleep(500);

    // 
    m_leds->SetLedMarquee(LineRandom);
    Common.Sleep(500);
    // m_leds->SetLedMarquee(LineRandom);
    // Common.Sleep(500);
    m_leds->SetLedMarquee(Snake);
    Common.Sleep(500);

    //
    // m_leds->SetLedMarquee(Pattern);
    m_leds->SetLedMarquee(TestAll);
    Common.Sleep(500);
}
#endif

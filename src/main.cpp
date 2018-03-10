#include <main.h>

#ifdef CUBE_3x3x3
const byte DIMENSIONS = 3;
#endif
#ifdef CUBE_4x4x4
const byte DIMENSIONS = 4;
#endif
#ifdef GAME
#include <CLedGame.h>

CLedGame* m_Game;
#endif

CLedMarquee* m_leds;

void setup()
{
    m_leds = new CLedMarquee(DIMENSIONS);
}

void loop()
{
    //
    m_leds->SetLedMarquee(TestAll);
    Common.Sleep(500);
    // m_leds->SetLedMarquee(TestAll);
    // Common.Sleep(500);

    // 
    m_leds->SetLedMarquee(Snake);
    Common.Sleep(500);
}
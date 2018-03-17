#include <main.h>

#ifdef GAME
#include <CLedGame.h>

CLedGame* m_Game;
#endif
#if defined(CUBE_3x3x3) || defined(CUBE_4x4x4)
#include <CLedMarquee.h>

CLedMarquee* m_leds;
#endif

#ifdef CUBE_3x3x3
const byte DIMENSIONS = 3;
#elif CUBE_4x4x4
const byte DIMENSIONS = 4;
#endif

void setup()
{
    m_leds = new CLedMarquee(DIMENSIONS);
}

void loop()
{
    //
    m_leds->SetLedMarquee(TestAll);
    Common.Sleep(500);

    // 
    // m_leds->SetLedMarquee(LineRandom);
    // Common.Sleep(500);
    // m_leds->SetLedMarquee(LineRandom);
    // Common.Sleep(500);
    // m_leds->SetLedMarquee(Snake);
    // Common.Sleep(500);

    //
    m_leds->SetLedMarquee(Pattern);
    m_leds->SetLedMarquee(TestAll);
    Common.Sleep(500);
}
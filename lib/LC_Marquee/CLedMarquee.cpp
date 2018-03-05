#include <CLedMarquee.h>

#pragma region Public methods

void CLedMarquee::ClearMarquee()
{
    m_leds->AllLedsOnOff(false);
}

void CLedMarquee::SetLedMarquee(ELedMarquee marquee)
{
    switch(marquee)
    {
        case TestAll:
            TestAllLeds();
            break;
        case Array:
// Set on 2 of the layers
for(int i = 0; i < 4; i += 2)
{
    m_leds->SetLedsLayerOnOff(i, true);
    Common.Sleep(SLEEP_60MS);
}
Common.Sleep(SLEEP_250MS);
for(int i = 1; i < 4; i += 2)
{
    m_leds->SetLedsLayerOnOff(i, true);
    Common.Sleep(SLEEP_60MS);
}
Common.Sleep(SLEEP_1S);
m_leds->AllLedsOnOff(false);

            break;
        case Mosaic:
    
            break;
        default:
            break;
    }
}

#pragma endregion

#pragma region Private methods

void CLedMarquee::TestAllLeds()
{


}

#pragma endregion
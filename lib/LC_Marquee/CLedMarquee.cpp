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

            break;
        case Mosaic:
            for (int i = 0; i < m_leds->GetDimensions(); i++)
            {
                m_leds->SetLedOnOff(0, i, 0, true);
                Common.Sleep(SLEEP_60MS);
            }
            for (int i = 0; i <= m_leds->GetDimensions(); i++)
            {
                m_leds->SetLedOnOff(i, i, 0, true);
                Common.Sleep(SLEEP_60MS);
            }
            break;
        default:
            break;
    }
}

#pragma endregion

#pragma region Private methods

void CLedMarquee::TestAllLeds()
{
    m_leds->AllLedsOnOff(true);
    Common.Sleep(SLEEP_250MS);
    m_leds->AllLedsOnOff(false);
    Common.Sleep(SLEEP_250MS);
}

#pragma endregion
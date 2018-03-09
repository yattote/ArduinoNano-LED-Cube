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
            for (int i = 0; i < m_iDimensions; i++)
            {
                SetLedsXyPlaneOnOff(i, 0);
                Common.Sleep(SLEEP_1S);
            }

            break;
        case Mosaic:
            for (int i = 0; i < m_iDimensions; i++)
            {
                m_leds->SetLedOnOff(0, i, 0, true);
                Common.Sleep(SLEEP_60MS);
            }
            for (int i = 0; i < m_iDimensions; i++)
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

void CLedMarquee::SetLedsXyPlaneOnOff(int x, int y)
{
    for (int k = 0; k < m_iDimensions; k++)
    {
        m_leds->SetLedOnOff(x, y, k, true);
        Common.Sleep(SLEEP_250MS);
    }
    Common.Sleep(SLEEP_500MS);
    for (int k = 0; k < m_iDimensions; k++)
    {
        m_leds->SetLedOnOff(x, y, k, false);
        Common.Sleep(SLEEP_250MS);
    }
}

void CLedMarquee::SetLedsLayerOnOff(int z)
{
    for (int i = 0; i < m_iDimensions; i++)
    {
        for (int j = 0; j < m_iDimensions; j++)
        {
            m_leds->SetLedOnOff(i, j, z, true);
            Common.Sleep(SLEEP_250MS);
        }
    }
    Common.Sleep(SLEEP_500MS);
    for (int i = 0; i < m_iDimensions; i++)
    {
        for (int j = 0; j < m_iDimensions; j++)
        {
            m_leds->SetLedOnOff(i, j, z, false);
            Common.Sleep(SLEEP_250MS);
        }
    }
}

#pragma endregion
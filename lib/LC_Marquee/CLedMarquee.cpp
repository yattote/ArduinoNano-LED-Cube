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
       
        case Mosaic:
            break;
        case LineVertical:
            for (i = 0; i < m_iDimensions; i++)
            {
                for (j = 0; j < m_iDimensions; j++)
                {
                    SetLedsXyPlaneVertical(i, j, false);
                    Common.Sleep(m_iSpeed * 2);      //move to next vertical column in (Speed * 2) ms
                }
            }
            break;
        case LineHorizontal:
            for (i = 0; i < m_iDimensions; i++)
            {
                for (k = 0; k < m_iDimensions; k++)
                {
                    SetLedsLayerHorizontal(i, k, false);
                    Common.Sleep(m_iSpeed * 2);
                }
            }
            break;
        case LineRandom:
            for (i = 0; i < m_iDimensions; i++)
            {
                //NOTE: random goes from 0 to [MAX - 1] values!
                if (random(2))
                {
                    SetLedsXyPlaneVertical(random(m_iDimensions), random(m_iDimensions), random(2));
                }
                else
                {
                    SetLedsLayerHorizontal(random(m_iDimensions), random(m_iDimensions), random(2));
                }
                Common.Sleep(m_iSpeed * 2);
            }
            break;
        case Snake:
            SetSnake(m_iDimensions * 2);
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

void CLedMarquee::SetLedsXyPlaneVertical(int x, int y, bool bTopToDown)
{
    for (k = 0; k < m_iDimensions; k++)
    {
        //direction from top to down through layers
        if (bTopToDown)
            m_leds->SetLedOnOff(x, y, k, true);
        else
            m_leds->SetLedOnOff(x, y, abs(k - m_iDimensions + 1), true);
        Common.Sleep(m_iSpeed);
    }
    
    // all column on, wait for (Speed * 2) ms
    Common.Sleep(m_iSpeed * 2);

    for (k = 0; k < m_iDimensions; k++)
    {
        if (bTopToDown)
            m_leds->SetLedOnOff(x, y, k, false);
        else
            m_leds->SetLedOnOff(x, y, abs(k - m_iDimensions + 1), false);
        Common.Sleep(m_iSpeed);
    }
}

void CLedMarquee::SetLedsLayerHorizontal(int x, int z, bool bLeftToRight)
{
    for (j = 0; j < m_iDimensions; j++)
    {
        //direction from left to right through layers
        if (bLeftToRight)
            m_leds->SetLedOnOff(x, j, z, true);
        else
            m_leds->SetLedOnOff(x, abs(j - m_iDimensions + 1), z, true);
        Common.Sleep(m_iSpeed);
    }
    
    // all row on, wait for (Speed * 2) ms
    Common.Sleep(m_iSpeed * 2);

    for (j = 0; j < m_iDimensions; j++)
    {
        if (bLeftToRight)
            m_leds->SetLedOnOff(x, j, z, false);
        else
            m_leds->SetLedOnOff(x, abs(j - m_iDimensions + 1), z, false);
        Common.Sleep(m_iSpeed);
    }
}

void CLedMarquee::SetSnake(int iIterations)
{
    int iValues[m_iDimensions], iNextDimension;

    //start in a random (x, y, z) position
    for (i = 0; i < m_iDimensions; i++)
    {
        iValues[i] = random(m_iDimensions);
    }
    for (i = 0; i < iIterations; i++)
    {
        //TODO: add memory to don't return to same place as the 3/4 previous movements
        //TODO: add snake's movement trail -> needs previous point to be implemented
        m_leds->SetLedOnOff(iValues[0], iValues[1], iValues[2], true);
        Common.Sleep(m_iSpeed * 3);
        m_leds->SetLedOnOff(iValues[0], iValues[1], iValues[2], false);

        // there are 3 dimensions and 2 possible directions per dimension
        iNextDimension = random(3);
        CalculateSnakeNextMove(0, iValues, iNextDimension, iNextDimension, random(2));
    }
}

void CLedMarquee::CalculateSnakeNextMove(int iIteration, int iValues[3], int iDimension, int iOrigDimension, bool bDirection)
{
    if (iIteration < 3)
    {
        if (bDirection && (iValues[iDimension] + 1) < m_iDimensions)
            iValues[iDimension]++;
        else if (!bDirection && (iValues[iDimension] - 1) >= 0)
            iValues[iDimension]--;
        else
            CalculateSnakeNextMove(iIteration + 1, iValues, (iDimension + 1) % 3, iOrigDimension, bDirection);
    }
    else
    {
        //go back in the original dimension
        if (bDirection)
            iValues[iOrigDimension]--;
        else
            iValues[iOrigDimension]++;
    }
}

#pragma endregion
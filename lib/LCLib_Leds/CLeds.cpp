#include "CLeds.h"

#define PLANETIME 2000      // time each plane is displayed in us -> 100 Hz refresh
#define TIMECONST 10        // multiplies DisplayTime to get ms

#pragma region Public methods

void CLeds::AllLedsOnOff(bool bLedsOn)
{
    for (int i = 0; i < m_iDimensions; i++)
    {
        for (int j = 0; j < m_iDimensions; j++)
        {
            digitalWrite(m_pinXY[i][j], bLedsOn);  // position pin to HIGH if switch ON and LOW if switch OFF
        }
        digitalWrite(m_pinZ[i], !bLedsOn);         // layer pin to LOW if switch ON and HIGH if switch OFF
    }
}

void CLeds::SetLedOnOff(int x, int y, int z, bool bLedOn)
{
    int iCountXY, iCountZ;

    //set new led status only if there is a change in this led
    if (m_ledStateXYZ[x][y][z] == bLedOn)
        return;
    else
        m_ledStateXYZ[x][y][z] = bLedOn;

    //count leds in columnn XY in ON state
    iCountXY = iCountZ = 0;
    for (int k = 0; k < m_iDimensions; k++)
    {
        if (m_ledStateXYZ[x][y][k])
            iCountXY++;
    }

    //count leds in plane Z in ON state
    for (int i = 0; i < m_iDimensions; i++)
    {
        for (int j = 0; j < m_iDimensions; j++)
        {
            if (m_ledStateXYZ[i][j][z])
                iCountZ++;
        }
    }

    //set corresponding pin status to switch ON/OFF the led
    if (bLedOn)
    {
        // all leds in column XY are OFF -> switch ON column XY
        if (iCountXY <= 1)
            digitalWrite(m_pinXY[x][y], HIGH);

        // all leds in plane Z are OFF -> switch ON plane Z
        if (iCountZ <= 1)
            digitalWrite(m_pinZ[z], LOW);
    }
    else
    {
        // all leds in column XY are OFF -> switch OFF column XY
        if (iCountXY == 0)
            digitalWrite(m_pinXY[x][y], LOW);

        // all leds in plane Z are OFF -> switch OFF plane Z
        if (iCountZ == 0)
            digitalWrite(m_pinZ[z], HIGH);
    }
}

void CLeds::SetPatternFromMem(unsigned char cPatternTable[])
{
    int iPlaneSize = m_iDimensions * m_iDimensions;
    byte PatternBuf[iPlaneSize];    // saves current pattern from PatternTable
    byte DisplayTime;               // time * 100ms to display pattern
    unsigned long lEndTime;
    int iPatternIdx;
    int iPatternBufIdx;             // indexes which byte from pattern buffer

    // Initialize iPatternIdx to beginning of pattern table
    iPatternIdx = 0;
    
    // loop over entries in pattern table - while DisplayTime > 0
    do
    {
        // read pattern from PROGMEM and save in array
        memcpy_P(PatternBuf, cPatternTable + iPatternIdx, iPlaneSize);
        iPatternIdx += iPlaneSize;

        // read DisplayTime from PROGMEM and increment index
        DisplayTime = pgm_read_byte_near(cPatternTable + iPatternIdx++);

        // compute lEndTime from current time (ms) and DisplayTime
        lEndTime = millis() + ((unsigned long) DisplayTime) * TIMECONST;

        // loop while (DisplayTime > 0) and (current time < lEndTime)
        while (millis() < lEndTime)
        {
            iPatternBufIdx = 0; // reset index counter to beginning of buffer
            // loop over planes
            for (int k = 0; k < m_iDimensions; k++)
            {
                if (k == 0)     // turn previous plane off
                {
                    digitalWrite(m_pinZ[m_iDimensions - 1], LOW);
                }
                else
                {
                    digitalWrite(m_pinZ[k - 1], LOW);
                }

                // load current plane pattern data into ports
                for (int i = 0; i < m_iDimensions; i++)
                {
                    for (int j = 0; j < m_iDimensions; j++)
                    {
                        digitalWrite(m_pinXY[i][j], PatternBuf[iPatternBufIdx] & (1 << j));
                    }
                    iPatternBufIdx++;
                }
                digitalWrite(m_pinZ[k], HIGH); // turn current plane on
                
                // delay PLANETIME us (2000us -> 2ms)
                delayMicroseconds(PLANETIME);
            }
        }
    } while (DisplayTime > 0);  // read patterns until time = 0 which signals end
}

#pragma endregion

// Private methods
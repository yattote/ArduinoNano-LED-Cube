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
            digitalWrite(m_xy[i][j], bLedsOn);  // position pin to HIGH if switch on and LOW if switch off
        }
        digitalWrite(m_z[i], !bLedsOn);         // layer pin to LOW if switch on and HIGH if switch off
    }
}

void CLeds::SetLedOnOff(int x, int y, int z,  bool bLedOn)
{
    // Set the desired LED position pin to HIGH if switch on and LOW if switch off
    // Set the desired LED layer pin to LOW if switch on and HIGH if switch off
    if (bLedOn)
    {
        // if no led in that column is ON, then switch ON
        if (m_bLedsOnXY[x][y] == 0 && digitalRead(m_xy[x][y]) == LOW)
        {
            digitalWrite(m_xy[x][y], HIGH);
        }
        m_bLedsOnXY[x][y]++;

        // if no led in that layer is ON, then switch ON
        if (m_bLedsOnZ[z] == 0 && digitalRead(m_z[z]) == HIGH)
        {
            digitalWrite(m_z[z], LOW);
        }
        m_bLedsOnZ[z]++;    //TODO: the control with array won't work if the same led is called twice
    }
    else
    {
        m_bLedsOnXY[x][y]--;
        // if all leds in that column is OFF, then switch OFF
        if (m_bLedsOnXY[x][y] == 0 && digitalRead(m_xy[x][y]) == HIGH)
        {
            digitalWrite(m_xy[x][y], LOW);
        }

        m_bLedsOnZ[z]--;
        // if all leds in that layer is OFF, then switch OFF
        if (m_bLedsOnZ[z] == 0 && digitalRead(m_z[z]) == LOW)
        {
            digitalWrite(m_z[z], HIGH);
        }
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
                    digitalWrite(m_z[m_iDimensions - 1], LOW);
                }
                else
                {
                    digitalWrite(m_z[k - 1], LOW);
                }

                // load current plane pattern data into ports
                for (int i = 0; i < m_iDimensions; i++)
                {
                    for (int j = 0; j < m_iDimensions; j++)
                    {
                        digitalWrite(m_xy[i][j], PatternBuf[iPatternBufIdx] & (1 << j));
                    }
                    iPatternBufIdx++;
                }
                digitalWrite(m_z[k], HIGH); // turn current plane on
                
                // delay PLANETIME us (2000us -> 2ms)
                delayMicroseconds(PLANETIME);
            }
        }
    } while (DisplayTime > 0);  // read patterns until time = 0 which signals end
}

#pragma endregion

// Private methods
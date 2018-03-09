#include "CLeds.h"

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
        if (m_bLedsOnXY[x][y] == 0 && digitalRead(m_xy[x][y]) == LOW)
        {
            digitalWrite(m_xy[x][y], HIGH);
        }
        m_bLedsOnXY[x][y]++;

        if (m_bLedsOnZ[z] == 0 && digitalRead(m_z[z]) == HIGH)
        {
            digitalWrite(m_z[z], LOW);
        }
        m_bLedsOnZ[z]++;    //TODO: the control with array won't work if the same led is called twice
    }
    else
    {
        m_bLedsOnXY[x][y]--;
        if (m_bLedsOnXY[x][y] == 0 && digitalRead(m_xy[x][y]) == HIGH)
        {
            digitalWrite(m_xy[x][y], LOW);
        }

        m_bLedsOnZ[z]--;
        if (m_bLedsOnZ[z] == 0 && digitalRead(m_z[z]) == LOW)
        {
            digitalWrite(m_z[z], HIGH);
        }
    }
}

#pragma endregion

// Private methods
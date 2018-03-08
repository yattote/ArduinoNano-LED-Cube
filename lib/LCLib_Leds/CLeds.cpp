#include "CLeds.h"

#pragma region Public methods

void CLeds::AllLedsOnOff(bool bLedsOn)
{
    for(i = 0; i < m_iDimensions; i++)
    {
        for(j = 0; j < m_iDimensions; j++)
        {
            digitalWrite(m_xy[i][j], bLedsOn); // position pin to HIGH if switch on and LOW if switch off
        }
        digitalWrite(m_z[i], !bLedsOn);         // layer pin to LOW if switch on and HIGH if switch off
    }
}

void CLeds::SetLedOnOff(int x, int y, int z,  bool bLedOn)
{
    // switch previous Led to idle [for horizontal movement in same layer]
    digitalWrite(m_xy[i][j], !bLedOn);
    if (z != k)
    {
        digitalWrite(m_z[z], bLedOn);
    }

    // Set the desired LED position pin to HIGH if switch on and LOW if switch off
    // Set the desired LED layer pin to LOW if switch on and HIGH if switch off
    digitalWrite(m_xy[x][y], bLedOn);
    digitalWrite(m_z[z], !bLedOn);

    // Set previous Led
    i = x;
    j = y;
    k = z;
}

void CLeds::SetLedsRowOnOff(int x, int z, bool bLedsOn)
{
    for(j = 0; j < m_iDimensions; j++)
    {
        SetLedOnOff(x, j, z, bLedsOn);
    }
}

void CLeds::SetLedsColOnOff(int y, int z, bool bLedsOn)
{
    for(i = 0; i < m_iDimensions; i++)
    {
        SetLedOnOff(i, y, z, bLedsOn);
    }
}

void CLeds::SetLedsLayerOnOff(int z, bool bLedsOn)
{
    for(i = 0; i < m_iDimensions; i++)
    {
        SetLedsRowOnOff(i, z, bLedsOn);
    }
}

#pragma endregion

// Private methods
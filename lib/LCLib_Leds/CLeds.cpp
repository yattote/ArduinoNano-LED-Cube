#include "CLeds.h"

#pragma region Public methods

void CLeds::AllLedsOnOff(bool bLedsOn)
{
    for(i = 0; i < m_iDimensions; i++)
    {
        for(j = 0; j < m_iDimensions; j++)
        {
            digitalWrite(m_xy[i][j], bLedsOn ? HIGH : LOW); // position pin to HIGH if switch on and LOW if switch off
        }
        digitalWrite(m_z[i], bLedsOn ? LOW : HIGH);         // layer pin to LOW if switch on and HIGH if switch off
    }
}

void CLeds::SetLedOnOff(int xy, int z,  bool bLedOn)
{
    digitalWrite(xy, bLedOn ? HIGH : LOW);  // Set the desired LED position pin to HIGH if switch on and LOW if switch off
    digitalWrite(z, bLedOn ? LOW : HIGH);   // Set the desired LED layer pin to LOW if switch on and HIGH if switch off
}

void CLeds::SetLedsRowOnOff(int x, int z, bool bLedsOn)
{
    for(j = 0; j < m_iDimensions; j++)
    {
        SetLedOnOff(m_xy[x][j], z, bLedsOn);
    }
}

void CLeds::SetLedsColOnOff(int y, int z, bool bLedsOn)
{
    for(i = 0; i < m_iDimensions; i++)
    {
        SetLedOnOff(m_xy[i][y], z, bLedsOn);
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
#include <Arduino.h>

/* xy-plane, Pin allocation:
 -|-------------------------------
 0| 0       1       2       3
 1| 4       5       6       7
 2| 8       9       10      11
 3| 12      13      14(A0)  15(A1)
 -|-------------------------------
 * 
 * z-axis (layers), Pin allocation:
-|-------------
3| 19(A5)
2| 18(A4)
1| 17(A3)
0| 16(A2)
-|-------------
 */

class CLeds
{
public:
    // Constructors
    CLeds(byte iDimensions)
    {
        m_iDimensions = iDimensions;
        m_xy = new byte*[iDimensions];      //init ROWS
        for (i = 0 ; i < iDimensions; i++ ) //init COLUMNS
            m_xy[i] = new byte[iDimensions];
        m_z = new byte[iDimensions];

        byte pin = 0;

        // Initialize and allocate pins 0 to 15
        for(i = 0; i < m_iDimensions; i++)
        {
            for(j = 0; j < m_iDimensions; j++)
            {
                m_xy[i][j] = pin++;             // Store and increment to next pin number and set pin as Output
                pinMode(m_xy[i][j], OUTPUT);
            }
        }

        // Allocate layers to array z, continue store pin starting from 16
        // TODO: check if this algorithm is the best way
        pin = m_iDimensions * m_iDimensions;
        for(i = 0; i < m_iDimensions; i++)
        {
            m_z[i] = pin++;
            pinMode(m_z[i], OUTPUT);            // Store and increment to next pin number and set pin as Output
        }
        AllLedsOnOff(false);    // Clear cube
    };

    // Public methods
    void AllLedsOnOff(bool bLedsOn);
    void SetLedOnOff(int xy, int z, bool bLedOn);
    void SetLedsRowOnOff(int x, int z, bool bLedsOn);
    void SetLedsColOnOff(int y, int z, bool bLedsOn);
    void SetLedsLayerOnOff(int z, bool bLedsOn);

private:
    // Fields
    byte m_iDimensions;
    byte** m_xy;    // array to store LED positions correspond to pin number
    byte*  m_z;     // array to store LED layers
    int i, j;       // Indices used in for loop

    // Private methods
};
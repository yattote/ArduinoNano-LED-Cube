#include <Arduino.h>

/* xy-plane, Pin allocation:
 -|-------------------------------
 3| 12      13      14(A0)  15(A1)
 2| 8       9       10      11
 1| 4       5       6       7
 0| 0       1       2       3
 -|-------------------------------
 * 
 * z-axis (layers), Pin allocation:
-|-------------
3| 16(A2)
2| 17(A3)
1| 18(A4)
0| 19(A5)
-|------------- */

class CLeds
{
public:
    // Constructors
    CLeds(int iDimensions)
    {
        m_iDimensions = iDimensions;
        m_xy = new byte*[iDimensions];      //init ROWS
        for (i = 0 ; i < iDimensions; i++ ) //init COLUMNS
            m_xy[i] = new byte[iDimensions];
        m_z = new byte[iDimensions];

        // Initialize and allocate pins 0 to 15
        byte pin = 0;
        for(i = 0; i < m_iDimensions; i++)
        {
            for(j = 0; j < m_iDimensions; j++)
            {
                m_xy[i][j] = pin++;  // Store and increment to next pin number and set pin as Output
                pinMode(m_xy[i][j], OUTPUT);
            }
        }

        // Allocate layers to array z, continue store pin starting from last XY-plane pin
        pin = m_iDimensions * m_iDimensions;
        for(i = 0; i < m_iDimensions; i++)
        {
            m_z[i] = pin++;
            pinMode(m_z[i], OUTPUT);                // Store and increment to next pin number and set pin as Output
        }
        AllLedsOnOff(false);    // Clear cube
    };

    // Public methods
    void AllLedsOnOff(bool bLedsOn);
    void SetLedOnOff(int x, int y, int z, bool bLedOn);
    void SetLedsRowOnOff(int x, int z, bool bLedsOn);
    void SetLedsColOnOff(int y, int z, bool bLedsOn);
    void SetLedsLayerOnOff(int z, bool bLedsOn);

    // Data accessors
	int GetDimensions()
	{
		return m_iDimensions;
	};
private:
    // Fields
    int m_iDimensions;
    byte** m_xy;    // array to store LED positions correspond to pin number
    byte*  m_z;     // array to store LED layers correspond to pin number
    bool** m_bXY;
    bool*  m_bZ;
    int i, j, k;    // Indices

    // Private methods
};
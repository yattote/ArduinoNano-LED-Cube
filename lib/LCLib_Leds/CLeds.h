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
        int i, j;

        // initialize variables
        m_iDimensions = iDimensions;
        m_xy = new byte*[iDimensions];      
        m_bLedsOnXY = new byte*[iDimensions];

        // initialize and allocate pins 0 to 15
        byte pin = 0;
        for (i = 0; i < m_iDimensions; i++)     //init ROWS
        {
            m_xy[i] = new byte[iDimensions];
            m_bLedsOnXY[i] = new byte[iDimensions];

            for (j = 0; j < m_iDimensions; j++) //init COLUMNS
            {
                m_xy[i][j] = pin++;  // Store and increment to next pin number and set pin as Output
                pinMode(m_xy[i][j], OUTPUT);
                m_bLedsOnXY[i][j] = 0;
            }
        }

        // allocate layers to array z, continue store pin starting from last XY-plane pin
        pin = m_iDimensions * m_iDimensions;
        m_z = new byte[iDimensions];
        m_bLedsOnZ = new byte[iDimensions];
        for (i = 0; i < m_iDimensions; i++)
        {
            m_z[i] = pin++;
            pinMode(m_z[i], OUTPUT);
            m_bLedsOnZ[i] = 0;
        }

        // clear cube
        AllLedsOnOff(false);
    };

    // Public methods
    void AllLedsOnOff(bool bLedsOn);
    void SetLedOnOff(int x, int y, int z, bool bLedOn);
    void SetPatternFromMem(unsigned char cPatternTable[]);

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
    byte** m_bLedsOnXY; //number of leds ON for each pin column
    byte*  m_bLedsOnZ;  //number of leds ON for each layer

    // Private methods
};
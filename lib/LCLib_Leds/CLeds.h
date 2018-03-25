#include <Arduino.h>

class CLeds
{
public:
    // Constructors
    CLeds(int iDimensions, int iPinsXY[], int iPinsZ[])
    {
        int i, j;

        // initialize variables
        m_iDimensions = iDimensions;
        m_xy = new byte*[iDimensions];      
        m_bLedsOnXY = new byte*[iDimensions];

        // initialize and allocate pins 0 to ([DIMENSIONS * 2] - 1)
        for (i = 0; i < m_iDimensions; i++)     //init ROWS
        {
            m_xy[i] = new byte[iDimensions];
            m_bLedsOnXY[i] = new byte[iDimensions];

            for (j = 0; j < m_iDimensions; j++) //init COLUMNS
            {
                m_xy[i][j] = iPinsXY[i * m_iDimensions + j];
                pinMode(m_xy[i][j], OUTPUT);
                m_bLedsOnXY[i][j] = 0;
            }
        }

        // allocate layers to array z, continue store pin starting from last XY-plane pin
        m_z = new byte[iDimensions];
        m_bLedsOnZ = new byte[iDimensions];
        for (i = 0; i < m_iDimensions; i++)
        {
            m_z[i] = iPinsZ[i];
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
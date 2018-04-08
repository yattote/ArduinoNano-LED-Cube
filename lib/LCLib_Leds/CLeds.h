#include <Arduino.h>

class CLeds
{
public:
    // Constructors
    CLeds(int iDimensions, int iPinsXY[], int iPinsZ[])
    {
        int i, j, k;

        // initialize variables
        m_iDimensions = iDimensions;
        m_pinXY = new byte*[iDimensions];      
        m_pinZ = new byte[iDimensions];
        m_ledStateXYZ = new bool**[iDimensions];      

        // process variables
        for (i = 0; i < m_iDimensions; i++)     //init ROWS X
        {
            m_pinXY[i] = new byte[iDimensions];
            m_ledStateXYZ[i] = new bool*[iDimensions];

            for (j = 0; j < m_iDimensions; j++) //init COLUMNS Y
            {
                // allocate pins to plane XY
                m_pinXY[i][j] = iPinsXY[i * m_iDimensions + j];
                pinMode(m_pinXY[i][j], OUTPUT);

                m_ledStateXYZ[i][j] = new bool[iDimensions];
                for (k = 0; k < m_iDimensions; k++)     //init PLANE Z
                {
                    m_ledStateXYZ[i][j][k] = false;
                }
            }

            // allocate pins to plane Z
            m_pinZ[i] = iPinsZ[i];
            pinMode(m_pinZ[i], OUTPUT);
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
    byte** m_pinXY;    // array to store LED positions correspond to pin number
    byte*  m_pinZ;     // array to store LED layers correspond to pin number
    bool*** m_ledStateXYZ;  // array to store each LED status (ON/OFF) corresponding to plane XYZ

    // Private methods
};
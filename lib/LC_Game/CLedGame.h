#include <Arduino.h>
#include <CLeds.h>

class CLedGame
{
public:
    // Constructors
    CLedGame(int iDimensions, int iPinsXY[], int iPinsZ[])
    {
        m_iDimensions = iDimensions;
        m_leds = new CLeds(iDimensions, iPinsXY, iPinsZ);
    };

    // Public methods
    void StartGame();

    // Data accessors
	int GetDimensions()
	{
		return m_iDimensions;
	};
private:
    // Fields
    int m_iDimensions;
    CLeds* m_leds;

    // Private methods
    void GeneratePixel();
    void ReadJoystick();
};
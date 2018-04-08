#include <Arduino.h>
#include <CLeds.h>
#include <CJoystick.h>
#include <CCommon.h>

const int IN_AXIS_X = 17;   //A3
const int IN_AXIS_Y = 18;   //A4
const int IN_BUTTON = 2;
const unsigned long TIME_TO_POWER_DOWN = 60000;
const unsigned long TIME_TO_CHANGE_LED = 3000;

class CLedGame
{
public:
    // Constructors
    CLedGame(int iDimensions, int iPinsXY[], int iPinsZ[])
    {
        m_leds = new CLeds(iDimensions, iPinsXY, iPinsZ);
        m_iDimensions = iDimensions;

        // set initial random X, Y, Z coordinates for leds
        m_iX = random(0, m_iDimensions);
        m_iY = random(0, m_iDimensions);
        m_iZ = random(0, m_iDimensions);
        m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
        m_iGenX = random(0, m_iDimensions);
        m_iGenY = random(0, m_iDimensions);
        m_iGenZ = random(0, m_iDimensions);
        m_leds->SetLedOnOff(m_iGenX, m_iGenY, m_iGenZ, true);
        m_lTimeLedOn = millis();

        m_joystick = new CJoystick(IN_AXIS_X, IN_AXIS_Y, IN_BUTTON);
        m_lastDirectionX = None;
        m_lastDirectionY = None;
        m_lLastTime = millis();
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
    CLeds* m_leds;
    int m_iDimensions;
    int m_iX, m_iY, m_iZ;           //current manual controlled LED
    int m_iGenX, m_iGenY, m_iGenZ;  //current generated LED
    unsigned long m_lTimeLedOn;
    CJoystick* m_joystick;
    EDirection m_lastDirectionX, m_lastDirectionY;
    int m_iButtonZ;
    unsigned long m_lLastTime;

    // Private methods
    void ReadJoystick();
    void MoveLed();
    void GenerateLed();
};
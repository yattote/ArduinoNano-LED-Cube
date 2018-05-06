#include <CLeds.h>
#include <CJoystick.h>
#include <CCommon.h>

const int IN_AXIS_X = 17;   //A3
const int IN_AXIS_Y = 18;   //A4
const int IN_BUTTON = 2;
const unsigned long TIME_TO_POWER_DOWN = 60000;     //1 minute
const int MAX_SIMON_LEVELS = 8;

enum class EGameMode { Unknown, Simon, User };
enum class EOrientation { Orientation0, Orientation90, Orientation180, Orientation270};

class CLedGame
{
public:
    // Constructors
    CLedGame(int iDimensions, int iPinsXY[], int iPinsZ[], EOrientation joystickOrientation)
    {
        m_leds = new CLeds(iDimensions, iPinsXY, iPinsZ);
        m_iDimensions = iDimensions;
        m_joystickOrientation = joystickOrientation;

        // set initial led for Simon list
        m_iSimonX = new int[MAX_SIMON_LEVELS];
        m_iSimonY = new int[MAX_SIMON_LEVELS];
        m_iSimonZ = new int[MAX_SIMON_LEVELS];
        m_iMaxLevel = 0;

        // set initial (X, Y, Z) coordinates for user led
        m_joystick = new CJoystick(IN_AXIS_X, IN_AXIS_Y, IN_BUTTON);
        m_iX = 0;
        m_iY = 0;
        m_iZ = 0;
        m_lastDirectionX = EDirection::None;
        m_lastDirectionY = EDirection::None;
        m_iCurrentLevel = 0;
        m_GameMode = EGameMode::Simon;
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
    EOrientation m_joystickOrientation;
    int* m_iSimonX;
    int* m_iSimonY;
    int* m_iSimonZ;             //list of generated LEDs for Simon game
    int m_iMaxLevel;            //max num. of leds for user to guess that sets if user has cleared current Simon level
    CJoystick* m_joystick;
    int m_iX, m_iY, m_iZ;       //current joystick controlled LED
    EDirection m_lastDirectionX, m_lastDirectionY;
    int m_iButtonZ;
    int m_iCurrentLevel;        //current led for user to guess
    EGameMode m_GameMode;       //flag to set if now user plays or Simon game plays
    unsigned long m_lLastTime;

    // Private methods
    void ReadJoystick();
    void MoveAndCheckLed();
    void SimonLed();
    void GenerateLed();
};
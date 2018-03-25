#include <CLedGame.h>

#pragma region Public methods

void CLedGame::StartGame()
{
    // TODO: generate random pixel
    // read (X, Y) position Joystick, and read button to change (Z) axis
}

#pragma endregion

#pragma region Private methods

void CLedGame::GeneratePixel()
{
    long rndX = random(0, m_iDimensions);
    long rndY = random(0, m_iDimensions);
    long rndZ = random(0, m_iDimensions);

}

void CLedGame::ReadJoystick()
{
    
}

#pragma endregion
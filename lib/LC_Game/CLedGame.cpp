#include <CLedGame.h>

#pragma region Public methods

void CLedGame::StartGame()
{
    // TODO: generate random vertical line
    // read (X, Y) position Joystick
    // check when led arrive bottom layer with position set with Joystick
}

#pragma endregion

#pragma region Private methods

void CLedGame::GenerateRandomVerticalLine()
{
    long rndX= random(0, m_iDimensions);
    long rndY= random(0, m_iDimensions);

    m_ledMarquee->SetLedMarquee(Mosaic);
}

void CLedGame::ReadJoystick()
{
    
}

#pragma endregion
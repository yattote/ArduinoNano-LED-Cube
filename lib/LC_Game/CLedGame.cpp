#include <CLedGame.h>

#pragma region Public methods

void CLedGame::StartGame()
{
    // read (X, Y) position Joystick, and read button to change (Z) axis
    ReadJoystick();

    // move LED only if Joystick has moved
    if (m_joystick->GetDirectionX() != None ||
        m_joystick->GetDirectionY() != None ||
        m_iButtonZ == LOW)
    {
        //reset count to PowerDown
        m_lLastTime = millis();

        //set changes to corresponding led
        m_lastDirectionX = m_joystick->GetDirectionX();
        m_lastDirectionY = m_joystick->GetDirectionY();
        MoveLed();

        Common.Sleep(250);
    }

    // Generate chased led
    // GenerateLed();

    // check if enter Power Down to save battery
	if (millis() - m_lLastTime >= TIME_TO_POWER_DOWN)
	{
        digitalWrite(LED_BUILTIN, HIGH);
		Common.PowerDown2();
        digitalWrite(LED_BUILTIN, LOW);
	}
}

#pragma endregion

#pragma region Private methods

void CLedGame::MoveLed()
{
    //switch off previous led
    m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, false);

    //check axis X
    if (m_lastDirectionX == Left)
        m_iX = (m_iX + 1 >= m_iDimensions) ? 0 : (m_iX + 1);
    else if (m_lastDirectionX == Right)
        m_iX = (m_iX - 1 < 0) ? (m_iDimensions - 1) : (m_iX - 1);

    //check axis Y
    if (m_lastDirectionY == Down)
        m_iY = (m_iY + 1 >= m_iDimensions) ? 0 : (m_iY + 1);
    else if (m_lastDirectionY == Up)
        m_iY = (m_iY - 1 < 0) ? (m_iDimensions - 1) : (m_iY - 1);

    //check axis Z
    if (m_iButtonZ == LOW)
        m_iZ = (m_iZ + 1 >= m_iDimensions) ? 0 : (m_iZ + 1);

    //switch on new led
    m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
#ifdef DEBUG
    Serial.println("LedX: " + String(m_iX) + " LedY: " + String(m_iY) + " LedZ: " + String(m_iZ));
#endif
}

void CLedGame::GenerateLed()
{
    /* PROBLEM -> common positive for columns and common grounds for same plane Z makes impossible to keep only two leds in different planes ON. Imagine following situation:
        - led (0, 0, 0) and led (0, 1, 1) are ON. You can think there should be only 2 leds ON but there are four:
        - led (0, 0, 0) , led (0, 1, 1), led (0, 1, 0), led (0, 1, 0) are ON as the two colums (0, 0) and (0, 1) and planes Z (0) and (1) are ON
       ALTERNATIVE -> make interactive only the last plane, and make chased led appear in the other m_iDimensions - 1 planes
    */
    if (millis() - m_lTimeLedOn >= TIME_TO_CHANGE_LED)
    {
        m_leds->SetLedOnOff(m_iGenX, m_iGenY, m_iGenZ, false);

        m_iGenX = random(0, m_iDimensions);
        m_iGenY = random(0, m_iDimensions);
        m_iGenZ = random(0, m_iDimensions);

        m_leds->SetLedOnOff(m_iGenX, m_iGenY, m_iGenZ, true);
        m_lTimeLedOn = millis();
    }
}

void CLedGame::ReadJoystick()
{
    m_iButtonZ = m_joystick->ReadButton();
#ifdef DEBUG
    int iX = m_joystick->ReadAxisX();
	int iY = m_joystick->ReadAxisY();
    
    Serial.println("X: " + String(iX) + " Y: " + String(iY) + " Button: " + String(m_iButtonZ) +
                   " DirectionX: " + String(m_joystick->GetDirectionX()) + " DirectionY: " + String(m_joystick->GetDirectionY()));
#else
    //we don't need values for axis (X, Y) because we just need direction
    m_joystick->ReadAxisX();
	m_joystick->ReadAxisY();
#endif
}

#pragma endregion
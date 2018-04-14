#include <CLedGame.h>

#pragma region Public methods

void CLedGame::StartGame()
{
    if (m_GameMode == User)
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
            MoveAndCheckLed();
        }

        // check if enter Power Down to save battery
        if (millis() - m_lLastTime >= TIME_TO_POWER_DOWN)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            Common.PowerDown2();
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
    else
    {
        SimonLed(); // Generate game leds and show them
    }
}

#pragma endregion

#pragma region Private methods

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

void CLedGame::MoveAndCheckLed()
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

#ifdef DEBUG
    Serial.println("LedX: " + String(m_iX) + " LedY: " + String(m_iY) + " LedZ: " + String(m_iZ));
#endif

    //check if moved led corresponds as led of Simon list
    if (m_iSimonX[m_iCurrentLevel] == m_iX &&
        m_iSimonY[m_iCurrentLevel] == m_iY &&
        m_iSimonZ[m_iCurrentLevel] == m_iZ)
    {
        //blink led to confirm led
        m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
        delay(1000);
        m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, false);
        delay(1000);
        m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
        delay(250);

        m_iCurrentLevel++;
    }
    else
    {
        //just switch on new led if doesn't match any led of Simon list
        m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
        delay(250);     //transition speed for user change between leds
    }

    // if user has complete sequence of Simon's level -> change GameMode flag and reset other variables
    if (m_iCurrentLevel == m_iMaxLevel - 1)//TODO: check user ans Simon levels
    {
        m_leds->AllLedsOnOff(true);
        delay(1000);
        m_leds->AllLedsOnOff(false);
        m_GameMode = Simon;
        m_iCurrentLevel = 0;
    }
}

void CLedGame::SimonLed()
{
    // add new led level by looping to make sure is different led than the previous level
    while (m_iMaxLevel > 0 &&
           m_iSimonX[m_iMaxLevel] == m_iSimonX[m_iMaxLevel - 1] &&
           m_iSimonY[m_iMaxLevel] == m_iSimonY[m_iMaxLevel - 1] &&
           m_iSimonZ[m_iMaxLevel] == m_iSimonZ[m_iMaxLevel - 1])
    {
        m_iSimonX[m_iMaxLevel] = random(0, m_iDimensions);
        m_iSimonY[m_iMaxLevel] = random(0, m_iDimensions);
        m_iSimonZ[m_iMaxLevel] = random(0, m_iDimensions);
    }

    // show all sequence with previous led and current new led
    for (int i = 0; i <= m_iMaxLevel; i++)
    {
        m_leds->SetLedOnOff(m_iSimonX[i], m_iSimonY[i], m_iSimonZ[i], true);
        delay(500);
        m_leds->SetLedOnOff(m_iSimonX[i], m_iSimonY[i], m_iSimonZ[i], false);
        delay(500);    //after blink, wait for the next led in the sequence
    }

    // change current level and change to user mode by blinking all
    m_GameMode = User;
    m_iMaxLevel++;
    if (m_iMaxLevel >= MAX_SIMON_LEVELS)
    {
        m_iMaxLevel = 0;
    }
    m_leds->AllLedsOnOff(true);
    delay(1000);
    m_leds->AllLedsOnOff(false);
    delay(250);

    // set also starting led for player
    m_leds->SetLedOnOff(m_iX, m_iY, m_iZ, true);
    delay(250);
}

void CLedGame::GenerateLed()
{
    /* PROBLEM -> common positive for columns and common grounds for same plane Z makes impossible to keep only two leds in different planes ON. Imagine following situation:
        - led (0, 0, 0) and led (0, 1, 1) are ON. You can think there should be only 2 leds ON but there are four:
        - led (0, 0, 0) , led (0, 1, 1), led (0, 1, 0), led (0, 1, 0) are ON as the two colums (0, 0) and (0, 1) and planes Z (0) and (1) are ON
       ALTERNATIVE -> make interactive only the last plane, and make chased led appear in the other m_iDimensions - 1 planes
    */
    /*if (millis() - m_lTimeLedOn >= TIME_TO_CHANGE_LED)
    {
        m_leds->SetLedOnOff(m_iSimonX, m_iSimonY, m_iSimonZ, false);

        m_iSimonX = random(0, m_iDimensions);
        m_iSimonY = random(0, m_iDimensions);
        m_iSimonZ = random(0, m_iDimensions - 1);

        m_leds->SetLedOnOff(m_iSimonX, m_iSimonY, m_iSimonZ, true);
        m_lTimeLedOn = millis();
    }*/
}

#pragma endregion
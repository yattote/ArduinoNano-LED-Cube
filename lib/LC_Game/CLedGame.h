#include <Arduino.h>
#include <CLedMarquee.h>

class CLedGame
{
public:
    // Constructors
    CLedGame(int iDimensions)
    {
        m_iDimensions = iDimensions;
        m_ledMarquee = new CLedMarquee(iDimensions);
    };

    // Public methods
    void StartGame();

private:
    // Fields
    int m_iDimensions;
    CLedMarquee* m_ledMarquee;

    // Private methods
    void GenerateRandomVerticalLine();
    void ReadJoystick();
};
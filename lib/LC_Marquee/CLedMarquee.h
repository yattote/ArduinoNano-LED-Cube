#include <CLeds.h>
#include <CCommon.h>

enum ELedMarquee { TestAll, LineVertical, LineHorizontal, LineRandom, Snake, Pattern };

class CLedMarquee
{
public:
    // Constructors
    CLedMarquee(int iDimensions, int iPinsXY[], int iPinsZ[])
    {
        m_iDimensions = iDimensions;
        m_leds = new CLeds(iDimensions, iPinsXY, iPinsZ);

        m_iSpeed = 60;
    };

    // Public methods
    void ClearMarquee();
    void SetLedMarquee(ELedMarquee marquee);

    void SetSpeed(int iSpeed)
    {
        m_iSpeed = iSpeed;    
    };

private:
    // Fields
    int m_iDimensions;
    CLeds* m_leds;
    int i, j, k;        //indexes for general use
    int m_iSpeed;

    // Private methods
    void TestAllLeds();
    void SetLedsXyPlaneVertical(int x, int y, bool bTopToDown);
    void SetLedsLayerHorizontal(int x, int z, bool bLeftToRight);
    void SetSnake(int iIterations);
    void CalculateSnakeNextMove(int iIteration, int iValues[3], int iDimension, int iOrigDimension, bool bDirection);
    void LoadPattern();
};

#include <Arduino.h>
#include <CLeds.h>
#include <CCommon.h>

enum ELedMarquee { TestAll, Array, Mosaic, LineVertical, LineHorizontal, LineDiagonal };

class CLedMarquee
{
public:
    // Constructors
    CLedMarquee(int iDimensions)
    {
        m_iDimensions = iDimensions;
        m_leds = new CLeds(iDimensions);
    };

    // Public methods
    void ClearMarquee();
    void SetLedMarquee(ELedMarquee marquee);

private:
    // Fields
    int m_iDimensions;
    CLeds* m_leds;

    // Private methods
    void TestAllLeds();
    void SetLedsXyPlaneOnOff(int x, int y);
    void SetLedsLayerOnOff(int z);
};
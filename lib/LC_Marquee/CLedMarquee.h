#include <Arduino.h>
#include <CLeds.h>
#include <CCommon.h>

enum ELedMarquee { TestAll, Array, Mosaic };

class CLedMarquee
{
public:
    // Constructors
    CLedMarquee(byte iDimensions)
    {
        m_iDimensions = iDimensions;
        m_leds = new CLeds(iDimensions);
    };

    // Public methods
    void ClearMarquee();
    void SetLedMarquee(ELedMarquee marquee);

private:
    // Fields
    byte m_iDimensions;
    CLeds* m_leds;

    // Private methods
    void TestAllLeds();
};
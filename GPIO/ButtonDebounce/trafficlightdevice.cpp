#include "trafficlightdevice.h"

#ifdef GPIO_RPI
#define GPIO_RED "24"
#define GPIO_YELLOW "5"
#define GPIO_GREEN "25"
#define GPIO_BUTTON "6"
#else
#define GPIO_RED "52"
#define GPIO_YELLOW "63"
#define GPIO_GREEN "53"
#define GPIO_BUTTON "93"

#endif // RPI vs. Toradex

TrafficLightDevice::TrafficLightDevice(TrafficLight &trafficLight)
    : m_trafficLight(trafficLight)
    , m_redlight(GPIO_RED)
    , m_yellowlight(GPIO_YELLOW)
    , m_greenlight(GPIO_GREEN)
    , m_walkbutton(GPIO_BUTTON)
{
    connect(&m_trafficLight, SIGNAL(lightStateChanged()), this, SLOT(handleLightStateChanged()));

    connect(&m_walkbutton, &GpioIn::lineStateChanged, this, &TrafficLightDevice::handleWalkPressed);
}

void TrafficLightDevice::handleWalkPressed(GpioIn::LineState state)
{
    if (state == GpioIn::High) {
        m_trafficLight.walk();
    }
}

void TrafficLightDevice::handleLightStateChanged()
{
    if (m_trafficLight.lightState() == TrafficLight::Go) {
        m_redlight.setLineState(GpioOut::Low);
        m_yellowlight.setLineState(GpioOut::Low);
        m_greenlight.setLineState(GpioOut::High);
    } else if (m_trafficLight.lightState() == TrafficLight::Slow) {
        m_redlight.setLineState(GpioOut::Low);
        m_yellowlight.setLineState(GpioOut::High);
        m_greenlight.setLineState(GpioOut::Low);
    } else {
        m_redlight.setLineState(GpioOut::High);
        m_yellowlight.setLineState(GpioOut::Low);
        m_greenlight.setLineState(GpioOut::Low);
    }
}

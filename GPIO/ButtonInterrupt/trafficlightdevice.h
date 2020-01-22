#ifndef TRAFFICLIGHTDEVICE_H
#define TRAFFICLIGHTDEVICE_H

#include <gpioin.h>
#include <gpioout.h>
#include <trafficlight.h>
#include <QSocketNotifier>

class TrafficLightDevice : public QObject
{
    Q_OBJECT
public:
    explicit TrafficLightDevice(TrafficLight &trafficLight);

protected slots:
    void handleLightStateChanged();
    void handleWalkPressed(GpioIn::LineState state);

private:
    TrafficLight &m_trafficLight;
    GpioOut m_redlight;
    GpioOut m_yellowlight;
    GpioOut m_greenlight;
    GpioIn m_walkbutton;
};

#endif // TRAFFICLIGHTDEVICE_H

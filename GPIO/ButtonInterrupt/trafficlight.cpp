#include "trafficlight.h"
#include <iostream>
#include <QFile>
#include <QString>
#include <QThread>
#include <QtDebug>

TrafficLight::TrafficLight()
{
    _timer.setInterval(500);
    _timer.start();

    connect(&_timer, SIGNAL(timeout()), this, SLOT(advanceLight()));
}

TrafficLight::LightState TrafficLight::lightState() const
{
    return _state;
}

void TrafficLight::setLightState(LightState state)
{
    if (state != _state) {
        _state = state;
        emit lightStateChanged();
    }
}

void TrafficLight::walk()
{
    setLightState(Stop);
    _timer.setInterval(3000);
}

void TrafficLight::advanceLight()
{
    _timer.setInterval(500);

    if (_state == Stop)
        setLightState(Go);
    else if (_state == Go)
        setLightState(Slow);
    else
        setLightState(Stop);
}

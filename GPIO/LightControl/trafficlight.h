#ifndef TRAFFLICLIGHT_H
#define TRAFFLICLIGHT_H

#include <QObject>
#include <QTimer>

class TrafficLight : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LightState lightState READ lightState NOTIFY lightStateChanged)

public:
    enum LightState { Stop = 0, Slow, Go };
    Q_ENUM(LightState)

    TrafficLight();
    LightState lightState() const;

public slots:
    void walk();

signals:
    void lightStateChanged();

private:
    void setLightState(LightState state);
    LightState _state{Stop};
    QTimer _timer;

private slots:
    void advanceLight();
};

#endif // TRAFFLICLIGHT_H

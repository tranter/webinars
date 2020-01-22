#ifndef GPIOOUT_H
#define GPIOOUT_H

#include <QFile>
#include <QObject>
#include <QString>

class GpioOut : public QObject
{
public:
    enum LineState { Low = 0, High };

    explicit GpioOut(const QString &gpioNumber);
    void setLineState(LineState state);
    int getLineState();

protected:
    void updateGpio();

signals:
    void lineStateChanged();

private:
    LineState _state;
    QString m_gpioNumber;
};

#endif // GPIOOUT_H

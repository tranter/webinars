#include "gpioout.h"
#include <QDebug>
#include <QFile>
#include <QThread>

GpioOut::GpioOut(const QString &gpioNumber)
    : _state(GpioOut::Low)
    , m_gpioNumber(gpioNumber)
{
    QFile exportFile("/sys/class/gpio/export");
    exportFile.open(QIODevice::WriteOnly | QIODevice::Text);
    exportFile.write(m_gpioNumber.toLatin1());
    exportFile.close();
    updateGpio();

    QFile directionFile("/sys/class/gpio/gpio" + gpioNumber + "/direction");
    if (!directionFile.open(QIODevice::WriteOnly))
        qWarning() << "cannot open " << directionFile.fileName();
    directionFile.write(QByteArray("out"));
    directionFile.close();
}

void GpioOut::setLineState(LineState state)
{
    if (state != _state) {
        _state = state;
        updateGpio();
    }
}

int GpioOut ::getLineState()
{
    return _state;
}

void GpioOut ::updateGpio()
{
    QFile file("/sys/class/gpio/gpio" + m_gpioNumber + "/value");
    file.open(QIODevice::WriteOnly | QIODevice::Text); // Open the file as a write only file
    if (_state == High) {
        file.write(QByteArray("1"));
    } else {
        file.write(QByteArray("0"));
    }
    file.close();
}

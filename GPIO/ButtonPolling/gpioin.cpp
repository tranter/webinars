#include "gpioin.h"

#include <QDebug>
#include <QSocketNotifier>

GpioIn::GpioIn(const QString &gpioNumber)
    : m_state(GpioIn::Low)
    , m_gpioNumber(gpioNumber)
    , m_valueFile(QString("/sys/class/gpio/gpio" + gpioNumber + "/value"))
{
    QFile exportFile("/sys/class/gpio/export");
    if (!exportFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qWarning() << "cannot open " << exportFile.fileName();
    exportFile.write(QByteArray(gpioNumber.toLatin1()));
    exportFile.close();

    QFile directionFile("/sys/class/gpio/gpio" + gpioNumber + "/direction");
    if (!directionFile.open(QIODevice::WriteOnly))
        qWarning() << "cannot open " << directionFile.fileName();
    directionFile.write(QByteArray("in"));
    directionFile.close();

    QFile edgeFile("/sys/class/gpio/gpio" + gpioNumber + "/edge");
    if (!edgeFile.open(QIODevice::WriteOnly))
        qWarning() << "cannot open " << edgeFile.fileName();
    edgeFile.write(QByteArray("both"));
    edgeFile.close();

    if (!m_valueFile.open(QIODevice::ReadOnly))
        qWarning() << "cannot open " << m_valueFile.fileName();
}

GpioIn::LineState GpioIn::lineState() const
{
    return m_state;
}

void GpioIn::updateGpio()
{
    m_valueFile.seek(0);
    QString string = m_valueFile.read(1);

    if (string == "0" && m_state != High) {
        qDebug() << "High";
        m_state = High;
        emit lineStateChanged(m_state);
    } else if (string == "1" && m_state != Low) {
        qDebug() << "Low";
        m_state = Low;
        emit lineStateChanged(m_state);
    }
}

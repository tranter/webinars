#ifndef GPIOIN_H
#define GPIOIN_H

#include <QFile>
#include <QFileDevice>
#include <QSocketNotifier>
#include <QTimer>

class GpioIn : public QObject
{
    Q_OBJECT
public:
    enum LineState { Low = 0, High };

    explicit GpioIn(const QString &gpioNumber);
    LineState lineState() const;
    void updateGpio();

signals:
    void lineStateChanged(GpioIn::LineState lineState);

private:
    LineState m_state;
    QString m_gpioNumber;
    QFile m_valueFile;
};

#endif // GPIOIN_H

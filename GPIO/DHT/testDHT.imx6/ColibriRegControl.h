#ifndef ColibriRegControl_H
#define ColibriRegControl_H

#include "GpioBasic.h"
// #include "GPIOModel.h"
#include <QElapsedTimer>

/***********************************************************************
 *
 * The ColibriRegControl class is able to control the direction and state of all GPIO pins
 * on the Colibri-iMX6's 40-pin header using the 'mmaping into /dev/mem' approach. The advantage
 * of this approach is that GPIO toggling speeds of up to 21MHz can be achieved
 * whereas the toggling gpio speed using the sysfs interface is in the 100s of KHz.
 *
 * This class is not comprehensive as it does not enable PAD manipulation, Pull-up control
 * or interrupts,but it is adequate for basic GPIO use
 *
 * *********************************************************************/

struct GpioPinStatus
{
    int phisNum;
    int linuxNum;
    int altMode;
    int inOutMode;
    int value;
};

class GpioPinDescription;

class ColibriRegControl : public GPIOBasic
{
    Q_OBJECT

public:
    explicit ColibriRegControl(int gpioNo = -1, QObject *parent = nullptr);

    virtual ~ColibriRegControl();

    virtual void setValue(int value);
    virtual int getValue();
    virtual void setDirection(const DirectionType &direction);
    virtual void setEdge(const EdgeType &edge);

    DirectionType getDirection();

protected slots:
    virtual void slotMonitor();

signals:

private slots:

private:
private:
    volatile uint32_t *m_gpioAddr;
    static const char *s_Alts[7];
};

#endif // ColibriRegControl_H

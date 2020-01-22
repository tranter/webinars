#ifndef GPIOBasic_H
#define GPIOBasic_H

#include <QObject>

class GPIOBasic : public QObject
{
    Q_OBJECT

public:
    // Enums
    enum EdgeType { None, Falling, Rising, Both };
    enum DirectionType { In, Out, Unknown };
    enum PinStatus { Low, High, NotDefined };

    GPIOBasic(QObject *parent = nullptr);
    virtual ~GPIOBasic();

    inline int value() { return m_value; }
    inline DirectionType direction() { return m_direction; }
    inline EdgeType edge() { return m_edge; }

    virtual int getValue() = 0;
    virtual void setValue(int value) = 0;
    virtual void setDirection(const DirectionType &direction) = 0;
    virtual void setEdge(const EdgeType &edge) = 0;

    void monitor();
    void quitThread();

signals:
    void sigValueChanged(bool new_value);

protected slots:
    virtual void slotMonitor() = 0;

protected:
    int m_pinNum = -1;
    int m_gpioNum = -1;
    int m_value = NotDefined;
    DirectionType m_direction = Unknown;
    EdgeType m_edge = None;

    // monitoring stuff
    QThread *m_thread = nullptr;
    int m_monitoringPeriod = 0; // 0 - forever
    bool m_isMonitoringMode = false;
    bool m_stopRequest = false;
};

#endif // GPIOBasic_H

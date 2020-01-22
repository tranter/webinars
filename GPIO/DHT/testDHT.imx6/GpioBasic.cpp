#include <QDir>
#include <QProcess>
#include <QThread>
#include <QTime>

#include "GpioBasic.h"

extern "C" {
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
}

GPIOBasic::GPIOBasic(QObject *parent)
    : QObject(parent)
    , m_pinNum(-1)
    , m_gpioNum(-1)
    , m_value(NotDefined)
    , m_direction(Unknown)
    , m_edge(None)
    , m_thread(nullptr)
    , m_monitoringPeriod(0)
    , m_isMonitoringMode(false)
    , m_stopRequest(false)
{}

GPIOBasic::~GPIOBasic()
{
    if (m_isMonitoringMode)
        quitThread();
}

void GPIOBasic::monitor()
{
    qInfo("GPIOMonitor::monitor start...");
    m_thread->start();
}

/**
 *
 * Separated thread for monitoring a GPIO pin
 *
 * @brief GPIOMonitor::slotDoMonitoring
 */
/*
void GPIOBasic::slotMonitor()
{
    qInfo("Start GPIO pin monitor: pin# = %d", m_gpioNum);
}
*/

void GPIOBasic::quitThread()
{
    qInfo("Quit thread in object: %p - %s", this, metaObject()->className());
    // I think it is not necessary to use a mutex here
    m_stopRequest = true;
    m_thread->quit();
    if (!m_thread->wait(550)) {
        m_thread->terminate();
        if (!m_thread->wait(600)) {
            qCritical("Time out on thread in object: %p - %s", this, metaObject()->className());
        }
    }
}

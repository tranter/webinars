extern "C" {
#include <cerrno>
#include <fcntl.h>
#include <cstdint>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
}

#include "ColibriRegControl.h"
#include <QTimer>

static uint32_t gpioBankAddr[7]
    = {0x0209C000, 0x020A0000, 0x020A4000, 0x020A8000, 0x020AC000, 0x020B0000, 0x020B4000};

const char *ColibriRegControl::s_Alts[7] = {"ALT0",
                                            "ALT1",
                                            "ALT2",
                                            "ALT3"
                                            "ALT4T",
                                            "ALT5",
                                            "ALT6",
                                            "ALT7"};

ColibriRegControl::ColibriRegControl(int gpioNo, QObject *parent)
    : GPIOBasic(parent)
    , m_gpioAddr(nullptr)
{
    m_gpioNum = gpioNo;
    if (m_gpioNum > 0) {
        int bank = m_gpioNum / 32;
        //int index = m_gpioNum % 32;
        int fd;

        //Obtain handle to physical memory
        if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
            qCritical("Unable to open /dev/mem: %s\n", strerror(errno));
        } else {
            size_t length = static_cast<size_t>(getpagesize()) * 250;
            m_gpioAddr = static_cast<uint32_t *>(
                mmap(nullptr, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpioBankAddr[bank]));

            if (m_gpioAddr == MAP_FAILED) {
                qCritical("mmap failed: %s\n", strerror(errno));
            }
            close(fd);
        }
    }
}

ColibriRegControl::~ColibriRegControl()
{
    // unmap GPIO registers (physicalmemory)  from process memory
    if ((m_gpioAddr != MAP_FAILED) && munmap((void *) m_gpioAddr, getpagesize() * 250) < 0) {
        qInfo("munmap (gpio) failed");
    }
}

void ColibriRegControl::setValue(int value)
{
    if (m_gpioAddr == MAP_FAILED || m_gpioNum < 0) {
        return;
    }

    int index = m_gpioNum % 32;

    // get pin status from GPIOx_GR
    if (value == 0) // 0 - clearing a bit
    {
        *m_gpioAddr &= ~(1 << index);
        m_value = PinStatus::Low;
    } else // 1 - setting a bit
    {
        *m_gpioAddr |= (1 << index);
        m_value = PinStatus::High;
    }
}

int ColibriRegControl::getValue()
{
    if (m_gpioAddr == MAP_FAILED || m_gpioNum < 0) {
        return PinStatus::NotDefined;
    }

    int index = m_gpioNum % 32;
    // get data bit from GPIOx_DR
    uint32_t reg = *m_gpioAddr;
    m_value = (((reg & (1 << index)) >> index) == 0) ? PinStatus::Low : PinStatus::High;
    return m_value;
}

void ColibriRegControl::setDirection(const DirectionType &direction)
{
    if (m_gpioAddr == MAP_FAILED || m_gpioNum < 0) {
        return;
    }

    int index = m_gpioNum % 32;

    int newmode = (direction == DirectionType::In) ? 0 : 1;

    if (newmode == 0) // IN - clearing a bit
    {
        *(m_gpioAddr + 1) &= ~(1 << index);
        m_direction = DirectionType::In;
    } else // OUT - setting a bit
    {
        *(m_gpioAddr + 1) |= (1 << index);
        m_direction = DirectionType::Out;
    }
}

GPIOBasic::DirectionType ColibriRegControl::getDirection()
{
    if (m_gpioAddr == MAP_FAILED || m_gpioNum < 0) {
        m_direction = DirectionType::Unknown;
    } else {
        int index = m_gpioNum % 32;
        // get data bit from GPIOx_DR
        uint32_t reg = *(m_gpioAddr + 1);
        reg = (reg & (1 << index)) >> index;
        if (((reg & (1 << index)) >> index) == 0)
            m_direction = DirectionType::In;
        else
            m_direction = DirectionType::Out;
    }

    return m_direction;
}

void ColibriRegControl::setEdge(const EdgeType &edge)
{
    Q_UNUSED(edge)
}

void ColibriRegControl::slotMonitor() {}

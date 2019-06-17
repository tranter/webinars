#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDebug>

/*

Simple CAN bus example. Tested on Linux platform.

To create a virtual CAN device, run the following commands:

sudo modprobe can
sudo modprobe can_raw
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

*/

int main()
{
    // Show enumerating the available plugins.
    qDebug() << "Available plugins:";
    for (auto plugin : QCanBus::instance()->plugins()) {
        qDebug() << "  " << plugin;
    }

    // Create device.
    QCanBusDevice *device = QCanBus::instance()->createDevice("socketcan", "vcan0");
    if (device != nullptr) {
        qDebug() << "Created device, state is:" << device->state();
    } else {
        qFatal("Unable to create CAN device.");
    }

    // Connect.
    if (device->connectDevice()) {
        qDebug() << "Connected, state is:" << device->state();
    } else {
        qDebug() << "Connect failed, error is:" << device->errorString();
    }

    // Create a data frame.
    QCanBusFrame frame(QCanBusFrame::DataFrame, "12345");

    // Send it.
    if (device->writeFrame(frame)) {
        qDebug() << "Wrote frame, state is:" << device->state();
    } else {
        qDebug() << "Write failed, error is:" << device->errorString();
    }

    // Disconnect.
    device->disconnectDevice();
    qDebug() << "Disconnected, state is:" << device->state();

    return 0;
}

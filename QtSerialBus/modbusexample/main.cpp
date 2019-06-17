#include <QDebug>
#include <QModbusDataUnit>
#include <QModbusTcpClient>
#include <QVector>

/*

Simple Modbus client example. Uses TCP network protocol. Tested on Linux platform. 
To make this actually work we would need to add an event loop.

*/

int main()
{
    // Create device.
    QModbusTcpClient *device = new QModbusTcpClient();
    if (device != nullptr) {
        qDebug() << "Created device, state is:" << device->state();
    } else {
        qFatal("Unable to create Modbus TCP client device.");
    }

    // Set connection parameters. Defaults to local host port 502.
    // Instead use TCP port 1502 as it is non-privileged.
    device->setConnectionParameter(QModbusDevice::NetworkPortParameter, 1502);

    // Connect.
    // We won't actually get from the "connecting" to "connected"
    // state without an event loop.
    if (device->connectDevice()) {
        qDebug() << "Connected, state is:" << device->state();
    } else {
        qDebug() << "Connect failed, error is:" << device->errorString();
    }

    // Create ADU.
    QVector<quint16> data(4);
    QModbusDataUnit adu(QModbusDataUnit::Coils, 1, data);

    // Send read request to a server at address 1.
    QModbusReply *reply = device->sendReadRequest(adu, 1);
    if (reply != nullptr) {
        qDebug() << "Sent read request, state is:" << device->state();
        qDebug() << reply;
    } else {
        qDebug() << "Send of read request failed, error is:" << device->errorString();
    }

    // Disconnect.
    device->disconnectDevice();
    qDebug() << "Disconnected, state is:" << device->state();

    return 0;
}

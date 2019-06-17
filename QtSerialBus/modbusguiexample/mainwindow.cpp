/*

 Simple Modbus client example. Uses TCP network protocol. Tested on
 Linux platform. Can test by connecting to Qt example
 <QTDIR>/examples/serialbus/modbus/slave/modbusslave.

*/

#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QModbusTcpClient>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create device.
    device = new QModbusTcpClient();
    if (device != nullptr) {
        ui->textEdit->append("Created device");
    } else {
        ui->textEdit->append("Unable to create Modbus TCP client device.");
    }

    // Connect signals and slots.
    connect(ui->quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendFrame);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::slotConnect);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::slotDisconnect);
    connect(device, &QModbusDevice::stateChanged, this, &MainWindow::stateChanged);

    // Show initial state.
    stateChanged(device->state());

    // Set connection parameters. Defaults to local host port 502.
    // Instead use TCP port 1502 as it is non-privileged.
    device->setConnectionParameter(QModbusDevice::NetworkPortParameter, 1502);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stateChanged(QModbusDevice::State state)
{
    QString name;

    switch (state) {
    case  QModbusDevice::UnconnectedState:
        name = "unconnected";
        break;
    case QModbusDevice::ConnectingState:
        name = "connecting";
        break;
    case QModbusDevice::ConnectedState:
        name = "connected";
        break;
    case QModbusDevice::ClosingState:
        name = "closing";
        break;
    default:
        name = "unknown";
        break;
    }

    ui->textEdit->append("State is: " + name);
}

void MainWindow::sendFrame()
{
    // Create ADU (this is incomplete).
    QVector<quint16> data(4);
    QModbusDataUnit adu(QModbusDataUnit::Coils, 1, data);

    // Send read request to a server at address 1.
    QModbusReply *reply = device->sendReadRequest(adu, 1);
    if (reply != nullptr) {
        ui->textEdit->append("Sent read request");
    } else {
        ui->textEdit->append("Send of read request failed, error is: " + device->errorString());
    }
}

void MainWindow::slotConnect()
{
    // Connect.
    if (device->connectDevice()) {
        ui->textEdit->append("Connected");
    } else {
        ui->textEdit->append("Connect failed, error is: " + device->errorString());
    }
}

void MainWindow::slotDisconnect()
{
    // Disconnect.
    device->disconnectDevice();
    ui->textEdit->append("Disconnected");
}

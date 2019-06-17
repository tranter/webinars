/*

 Simple CAN bus example. Tested on Linux platform.

 To create a virtual CAN device, run the following commands:

 sudo modprobe can
 sudo modprobe can_raw
 sudo modprobe vcan
 sudo ip link add dev vcan0 type vcan
 sudo ip link set up vcan0

*/

#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create device.
    device = QCanBus::instance()->createDevice("socketcan", "vcan0");
    if (device != nullptr) {
        ui->textEdit->append("Created socketcan device vcan0");
    } else {
        ui->textEdit->append("Unable to create CAN device.");
    }

    // Connect signals and slots.
    connect(ui->quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendFrame);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::slotConnect);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::slotDisconnect);
    connect(device, &QCanBusDevice::stateChanged, this, &MainWindow::stateChanged);

    // Show initial state.
    stateChanged(device->state());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stateChanged(QCanBusDevice::CanBusDeviceState state)
{
    QString name;

    switch (state) {
    case  QCanBusDevice::UnconnectedState:
        name = "unconnected";
        break;
    case QCanBusDevice::ConnectingState:
        name = "connecting";
        break;
    case QCanBusDevice::ConnectedState:
        name = "connected";
        break;
    case QCanBusDevice::ClosingState:
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
    // Create a data frame.
    QCanBusFrame frame(QCanBusFrame::DataFrame, "12345");

    // Send it.
    if (device->writeFrame(frame)) {
        ui->textEdit->append("Wrote frame");
    } else {
        ui->textEdit->append("Write failed, error is: " + device->errorString());
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

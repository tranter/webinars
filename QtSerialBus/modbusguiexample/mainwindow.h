#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusTcpClient>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void stateChanged(QModbusDevice::State state);
    void sendFrame();
    void slotConnect();
    void slotDisconnect();

private:
    Ui::MainWindow *ui;
    QModbusTcpClient *device;
};

#endif // MAINWINDOW_H

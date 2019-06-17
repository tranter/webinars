#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCanBusDevice>

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
    void stateChanged(QCanBusDevice::CanBusDeviceState state);
    void sendFrame();
    void slotConnect();
    void slotDisconnect();

private:
    Ui::MainWindow *ui;
    QCanBusDevice *device;
};

#endif // MAINWINDOW_H

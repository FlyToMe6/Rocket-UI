#ifndef BLUETOOTHDIALOG_H
#define BLUETOOTHDIALOG_H

#include <QDialog>
#include <QBluetoothDeviceDiscoveryAgent>
#include<QListWidget>

namespace Ui {
class bluetoothDialog;
}

class bluetoothDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bluetoothDialog(QWidget *parent = nullptr);
    ~bluetoothDialog();

signals:
    void sendName(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

private:
    Ui::bluetoothDialog *ui;

    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QString string;
    bool k = false;
};

#endif // BLUETOOTHDIALOG_H

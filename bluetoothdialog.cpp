#include "bluetoothdialog.h"
#include "ui_bluetoothdialog.h"

bluetoothDialog::bluetoothDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bluetoothDialog)
{
    ui->setupUi(this);

    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    agent->start();
}

bluetoothDialog::~bluetoothDialog()
{
    delete ui;
}

void bluetoothDialog::on_pushButton_clicked()
{
    ui->listWidget->clear();
    agent->stop();
    agent->start();
}


void bluetoothDialog::on_pushButton_2_clicked()
{
    this->close();
    emit sendName(string);
}


void bluetoothDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    string = item->text();
}

void bluetoothDialog::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QtBluetooth/qbluetoothserver.h>
#include <QtBluetooth/qbluetoothsocket.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bleDial = new bluetoothDialog();
    nbForm = new numbersForm();

    currentPlotTab = new QCustomPlot;

    //set flag about the absence of data on the charts
    flag = false;

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(bleDial, &bluetoothDialog::sendName, this, &MainWindow::setBleDeviceName );
    connect(nbForm, &numbersForm::sendCommand, this, &MainWindow::sendMSG );
    connect(socket, &QBluetoothSocket::readyRead, this, &MainWindow::readMessage);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    if (bleDeviceName != nullptr)
    {
        sendMSG("S");
    }
    else
    {
        QMessageBox::information(0, "info", "No device selected");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    logFilePath = QFileDialog::getOpenFileName(this, "Open config file", QDir::homePath());
    startReplot(logFilePath);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked()){
        loadFile(logFilePath);
    }
    if(ui->radioButton_2->isChecked()){
        loadFile(configFilePath);
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    configFilePath = QFileDialog::getOpenFileName(this, "Open config file", QDir::homePath());
}

void MainWindow::loadFile(QString fileType)
{
    QFile file(fileType);

    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
    file.close();
}

void MainWindow::startReplot(QString fileLog)
{
    //parser for log file
    QFile file(fileLog);
      if(file.open(QIODevice::ReadOnly |QIODevice::Text))
      {
          while(!file.atEnd())
          {
              QString str = file.readLine();
              QStringList lst = str.split(",");

              angle_X.push_back(lst.at(0).toDouble());
              angle_Y.push_back(lst.at(1).toDouble());
              angle_Z.push_back(lst.at(2).toDouble());

              axeleration_X.push_back(lst.at(3).toDouble());
              axeleration_Y.push_back(lst.at(4).toDouble());
              axeleration_Z.push_back(lst.at(5).toDouble());

              speed_X.push_back(lst.at(6).toDouble());
              speed_Y.push_back(lst.at(7).toDouble());
              speed_Z.push_back(lst.at(8).toDouble());

              control_X.push_back(lst.at(9).toDouble());
              control_Y.push_back(lst.at(10).toDouble());
              control_Z.push_back(lst.at(11).toDouble());

              T.push_back(lst.at(13).toDouble());
          }

      }



    replotAxis(ui->anglesPlot, 0, T, angle_X, "red", flag);
    replotAxis(ui->anglesPlot, 1, T, angle_Y, "blue", flag);
    replotAxis(ui->anglesPlot, 2, T, angle_Z, "green", flag);

    replotAxis(ui->axelerationsPlot, 0, T, axeleration_X, "orange", flag);
    replotAxis(ui->axelerationsPlot, 1, T, axeleration_Y, "yellow", flag);
    replotAxis(ui->axelerationsPlot, 2, T, axeleration_Z, "magenta", flag);

    replotAxis(ui->speedsPlot, 0, T, speed_X,"yellow", flag);
    replotAxis(ui->speedsPlot, 1, T, speed_Y, "red", flag);
    replotAxis(ui->speedsPlot, 2, T, speed_Z, "blue", flag);

    replotAxis(ui->controlsPlot, 0, T, control_X, "magenta", flag);
    replotAxis(ui->controlsPlot, 1, T, control_Y, "green", flag);
    replotAxis(ui->controlsPlot, 2, T, control_Z, "red", flag);

    flag = true;

    angle_X.clear();
    angle_Y.clear();
    angle_Z.clear();
    T.clear();
    speed_X.clear();
    speed_Y.clear();
    speed_Z.clear();
    axeleration_X.clear();
    axeleration_Y.clear();
    axeleration_Z.clear();
    control_X.clear();
    control_Y.clear();
    control_Z.clear();
}

void MainWindow::setLines(QCustomPlot *Plot, double xmin, double xmax, double ymin, double ymax)
{

    Plot->xAxis->setRange(xmin, xmax);
    Plot->yAxis->setRange(ymin, ymax);
    Plot->replot();



}

void MainWindow::replotAxis(QCustomPlot *Plot, int graphNumber, QVector<double> T, QVector<double> Y, QString lineColor, bool flag)
{
    if(flag == true)
    {
        Plot->graph(graphNumber)->data()->clear();
    }
    Plot->addGraph();
    Plot->graph(graphNumber)->addData(T,Y);
    Plot->graph(graphNumber)->setPen(QPen(lineColor));
    Plot->addGraph();
    Plot->setInteraction(QCP::iRangeZoom, true);
    Plot->setInteraction(QCP::iRangeDrag,true);
    Plot->setInteraction(QCP::iSelectPlottables,true);
    Plot->replot();
}


void MainWindow::on_pushButton_7_clicked()
{
    currentPlotTab = ui->tabWidget->currentWidget()->findChild<QCustomPlot*>();

    if(ui->radioButton_6->isChecked()){
        setLines(currentPlotTab, 0, 25, 0, 20);
    }

    if(ui->radioButton_5->isChecked()){
        try{

            xMin = ui->lineEdit->text().toDouble();
            xMax = ui->lineEdit_2->text().toDouble();
            yMin = ui->lineEdit_3->text().toDouble();
            yMax = ui->lineEdit_4->text().toDouble();

            setLines(currentPlotTab, xMin, xMax, yMin, yMax);
        }

        catch(bool error){
            QMessageBox::information(0, "info", "numbers only");
        }
    }

}


void MainWindow::on_pushButton_6_clicked()
{
    currentPlotTab = ui->tabWidget->currentWidget()->findChild<QCustomPlot*>();
    setLines(currentPlotTab, 0, 5, 0, 5);
}


void MainWindow::on_pushButton_9_clicked()
{
    currentPlotTab = ui->tabWidget->currentWidget()->findChild<QCustomPlot*>();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a filename to save under"), QString(),
                                                    tr("PNG(*.png);;JPG(*.jpg);;PDF(*.pdf);;BMP(*.bmp);;All Files(*)"));
    if(!fileName.isEmpty())
        {
            if(fileName.endsWith(".png", Qt::CaseInsensitive))
            {
                currentPlotTab->savePng(fileName);
            }
            else if(fileName.endsWith(".jpg", Qt::CaseInsensitive))
            {
                currentPlotTab->saveJpg(fileName);
            }
            else if(fileName.endsWith(".pdf", Qt::CaseInsensitive))
            {
                currentPlotTab->savePdf(fileName);
            }
            else if(fileName.endsWith(".bmp", Qt::CaseInsensitive))
            {
                currentPlotTab->saveBmp(fileName);
            }
            else
            {
                fileName += ".png";
                currentPlotTab->savePng(fileName);
            }
        }

}


void MainWindow::on_pushButton_8_clicked()
{
    nbForm->show();
}


void MainWindow::on_pushButton_10_clicked()
{
    bleDial->show();
}

void MainWindow::setBleDeviceName(QString name)
{
    bleDeviceName = name;
}

void MainWindow::sendMSG(const char *msg)
{
    socket->write(msg);
}

void MainWindow::readMessage()
{
    do
    {
        line += socket->readLine().trimmed();
        ui->BluetoothReadShow->setText(QString::fromUtf8(line.constData(), line.length()));

    } while (socket->canReadLine());


}


void MainWindow::on_pushButton_11_clicked()
{
    if (bleDeviceName != nullptr)
    {
        static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
        socket->connectToService(QBluetoothAddress(bleDeviceName), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
        
    }
    else
    {
        QMessageBox::information(0, "info", "No device selected");
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag = false;


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    rocketWindow.show();
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
    startReplot(configFilePath);
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
    //parser imitator, to do: add parser
    for(double i = 0; i < 20; i++){
           angle_X.push_back(i);
           angle_Y.push_back(i+1);
           angle_Z.push_back(i-1);
           T.push_back(i);
           speed_X.push_back(i+1);
           speed_Y.push_back(i-1);
           speed_Z.push_back(i);
           axeleration_X.push_back(i+1);
           axeleration_Y.push_back(i-1);
           axeleration_Z.push_back(i);
           control_X.push_back(i+1);
           control_Y.push_back(i-1);
           control_Z.push_back(i);
    }

    replotAxis(ui->anglesPlot, 0, T, angle_X, "red", flag);
    replotAxis(ui->anglesPlot, 0, T, angle_Y, "blue", flag);
    replotAxis(ui->anglesPlot, 0, T, angle_Z, "green", flag);

    replotAxis(ui->axelerationsPlot, 0, T, axeleration_X, "orange", flag);
    replotAxis(ui->axelerationsPlot, 0, T, axeleration_Y, "yellow", flag);
    replotAxis(ui->axelerationsPlot, 0, T, axeleration_Z, "magenta", flag);

    replotAxis(ui->speedsPlot, 0, T, speed_X,"yellow", flag);
    replotAxis(ui->speedsPlot, 0, T, speed_Y, "red", flag);
    replotAxis(ui->speedsPlot, 0, T, speed_Z, "blue", flag);

    replotAxis(ui->controlsPlot, 0, T, control_X, "magenta", flag);
    replotAxis(ui->controlsPlot, 0, T, control_Y, "green", flag);
    replotAxis(ui->controlsPlot, 0, T, control_Z, "red", flag);

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

void MainWindow::defaultLines(QCustomPlot *Plot)
{

    Plot->xAxis->setRange(0,25);
    Plot->yAxis->setRange(0,20);
    Plot->setInteraction(QCP::iRangeZoom, true);
    Plot->setInteraction(QCP::iRangeDrag,true);
    Plot->setInteraction(QCP::iSelectPlottables,true);
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
    Plot->replot();
}


void MainWindow::on_pushButton_7_clicked()
{
    defaultLines(ui->axelerationsPlot);
    defaultLines(ui->anglesPlot);
    defaultLines(ui->controlsPlot);
    defaultLines(ui->speedsPlot);
}


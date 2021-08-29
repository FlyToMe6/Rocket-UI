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
           angle_X.push_back(i+double(1+rand()%3));
           angle_Y.push_back(i+1+double(1+rand()%3));
           angle_Z.push_back(i-1+double(1+rand()%3));
           T.push_back(i);
           speed_X.push_back(i+1+double(1+rand()%3));
           speed_Y.push_back(i-1+double(1+rand()%3));
           speed_Z.push_back(i+double(1+rand()%3));
           axeleration_X.push_back(i+1+double(1+rand()%3));
           axeleration_Y.push_back(i-1+double(1+rand()%5));
           axeleration_Z.push_back(i+double(1+rand()%3));
           control_X.push_back(i+1+double(1+rand()%2));
           control_Y.push_back(i-1+double(1+rand()%3));
           control_Z.push_back(i+double(1+rand()%4));
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
    if(ui->radioButton_6->isChecked()){
        setLines(ui->axelerationsPlot, 0, 25, 0, 20);
        setLines(ui->anglesPlot, 0, 25, 0, 20);
        setLines(ui->controlsPlot, 0, 25, 0, 20);
        setLines(ui->speedsPlot, 0, 25, 0, 20);
    }
    if(ui->radioButton_5->isChecked()){
        try{
            xMin = ui->lineEdit->text().toDouble();
            xMax = ui->lineEdit_2->text().toDouble();
            yMin = ui->lineEdit_3->text().toDouble();
            yMax = ui->lineEdit_4->text().toDouble();


            setLines(ui->axelerationsPlot, xMin, xMax, yMin, yMax);
        }
        catch(bool error){
            QMessageBox::information(0, "info", "numbers only");
        }
    }

}


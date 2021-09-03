#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qcustomplot.h>
#include <QVector>
#include <QtMath>
#include <bluetoothdialog.h>
#include <QBluetoothSocket>
#include <numbersform.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setBleDeviceName(QString name);


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();


private:

    Ui::MainWindow *ui;
    bluetoothDialog *bleDial;
    numbersForm *nbForm;

    void loadFile(QString fileType);
    void startReplot(QString fileLog);
    void setLines(QCustomPlot *Plot, double xmin, double xmax, double ymin, double ymax);
    void replotAxis(QCustomPlot *Plot, int graphNumber, QVector<double> T, QVector<double> Y, QString lineColor, bool flag);

    QCustomPlot *wGraphic;      // Объявляем объект QCustomPlot
    QCustomPlot *currentPlotTab;
    QVector<QCustomPlot> Plots;
    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;      // Трасировщик по точкам графика

    //data for plot
    QVector<double> angle_X, angle_Y, angle_Z, T;
    QVector<double> speed_X, speed_Y, speed_Z;
    QVector<double> axeleration_X, axeleration_Y, axeleration_Z;
    QVector<double> control_X, control_Y, control_Z;

    bool flag;

    double xMin, xMax, yMin, yMax;

    QString configFilePath, logFilePath;
    //ble
    QString bleDeviceName;
    QBluetoothSocket *socket;
};
#endif // MAINWINDOW_H

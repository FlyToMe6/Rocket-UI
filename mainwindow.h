#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qcustomplot.h>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <qmlrocketwindow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    qmlRocketWindow rocketWindow;
    QCustomPlot *wGraphic;      // Объявляем объект QCustomPlot
    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;      // Трасировщик по точкам графика
    QVector<double> angle_X, angle_Y, angle_Z, T;
    QVector<double> speed_X, speed_Y, speed_Z;
    QVector<double> axeleration_X, axeleration_Y, axeleration_Z;
    QVector<double> control_X, control_Y, control_Z;
    QVector<double> thrust;
    bool flag;
};
#endif // MAINWINDOW_H

#include "qmlrocketwindow.h"
#include "ui_qmlrocketwindow.h"
#include <QUrl>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>

qmlRocketWindow::qmlRocketWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qmlRocketWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/rocketWindow.qml"));
    ui->quickWidget->show();
}

qmlRocketWindow::~qmlRocketWindow()
{
    delete ui;
}

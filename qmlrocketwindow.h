#ifndef QMLROCKETWINDOW_H
#define QMLROCKETWINDOW_H

#include <QWidget>

namespace Ui {
class qmlRocketWindow;
}

class qmlRocketWindow : public QWidget
{
    Q_OBJECT

public:
    explicit qmlRocketWindow(QWidget *parent = nullptr);
    ~qmlRocketWindow();

private:
    Ui::qmlRocketWindow *ui;
};

#endif // QMLROCKETWINDOW_H

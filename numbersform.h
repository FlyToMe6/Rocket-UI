#ifndef NUMBERSFORM_H
#define NUMBERSFORM_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class numbersForm;
}

class numbersForm : public QWidget
{
    Q_OBJECT

public:
    explicit numbersForm(QWidget *parent = nullptr);
    ~numbersForm();

signals:
    void sendCommand(const char*);


private slots:
    void thisCommand();

private:
    Ui::numbersForm *ui;
    QList<QPushButton *> allPButtons;
};

#endif // NUMBERSFORM_H

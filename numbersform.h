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
 /*   void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();*/

private:
    Ui::numbersForm *ui;
    QList<QPushButton *> allPButtons;
};

#endif // NUMBERSFORM_H

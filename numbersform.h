#ifndef NUMBERSFORM_H
#define NUMBERSFORM_H

#include <QWidget>

namespace Ui {
class numbersForm;
}

class numbersForm : public QWidget
{
    Q_OBJECT

public:
    explicit numbersForm(QWidget *parent = nullptr);
    ~numbersForm();

private:
    Ui::numbersForm *ui;
};

#endif // NUMBERSFORM_H

#include "numbersform.h"
#include "ui_numbersform.h"

numbersForm::numbersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::numbersForm)
{
    ui->setupUi(this);
}

numbersForm::~numbersForm()
{
    delete ui;
}

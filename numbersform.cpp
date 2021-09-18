#include "numbersform.h"
#include "ui_numbersform.h"

numbersForm::numbersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::numbersForm)
{
    ui->setupUi(this);

    allPButtons = findChildren<QPushButton *>();

        for(int i = 0; i < allPButtons.size(); i++)
        {
            QObject::connect(allPButtons.at(i), SIGNAL(clicked()), this,SLOT(thisCommand()));
        }

}

numbersForm::~numbersForm()
{
    delete ui;
}

void numbersForm::thisCommand()
{
    //send buttons text via bluetooth to device
    emit sendCommand(qobject_cast<QPushButton *>(sender())->text().toUtf8());
}

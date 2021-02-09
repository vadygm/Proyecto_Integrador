#include "dialog_save.h"
#include "ui_dialog_save.h"
#include <QDebug>

Dialog_Save::Dialog_Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Save)
{
    ui->setupUi(this);
}

Dialog_Save::~Dialog_Save()
{
    delete ui;
}
//-----------------------------------------
//-----------------------------------------
void Dialog_Save::on_cm_Yes_clicked()
{
    desitio = 'y';
    close();
}

void Dialog_Save::on_cm_No_clicked()
{
    desitio = 'n';
    close();
}

void Dialog_Save::on_cm_Cancel_clicked()
{
    desitio = 'c';
    close();
}

char Dialog_Save::getDesitio() const
{
    return desitio;
}

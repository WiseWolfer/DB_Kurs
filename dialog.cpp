#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
    ,ui(new Ui::Dialog)

  //инициализация валидаторов
    ,val_HOST_NAME(QRegExp("^[0-9]\{3}\\.[0-9]\{1}\\.[0-9]\{1}\\.[0-9]\{1}$"))
    ,val_Port(QRegExp("^[0-9]\{4}$"))
{
    ui->setupUi(this);
    //установка валидаторов
    ui->lineEditServer->setValidator(&val_HOST_NAME);
    ui->lineEdit_Port->setValidator(&val_Port);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getHost_name() const
{
    return ui->lineEditServer->text();
}

int Dialog::getPort() const
{
    return ui->lineEdit_Port->text().toInt();
}

QString Dialog::getDatabasename() const
{
    return ui->lineEdit_Database->text();
}

QString Dialog::getUsername() const
{
    return ui->lineEdit_Username->text();
}

QString Dialog::getPassword() const
{
    return ui->lineEdit_Password->text();
}

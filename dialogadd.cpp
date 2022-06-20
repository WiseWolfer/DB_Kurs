#include "dialogadd.h"
#include "ui_dialogadd.h"

#include <string>
#include <QString>
#include <iostream>

DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent)
  ,ui(new Ui::DialogAdd)

  //инициализация валидаторов
  ,val_name_of_na(QRegExp("^[А-я]\{1,20}\\s[А-я]\{1,20}\\s[А-я]\{0,20}\\s[А-я]\{0,20}\\s[А-я]\{0,20}$"))
  ,val_type_of_na(QRegExp("^[А-я]\{1,20}$"))
  ,val_resp_person(QRegExp("^[А-я]\{1,20}\\s[А-я]\{1,20}\\s[А-я]\{1,20}$"))
{
    ui->setupUi(this);

    //установка валидаторов
    ui->lineEdit_Name_na->setValidator(&val_name_of_na);
    ui->lineEdit_Type_of_na->setValidator(&val_type_of_na);
    ui->lineEdit_Responsbile_person->setValidator(&val_resp_person);
}

DialogAdd::~DialogAdd()
{
    delete ui;
}


QString DialogAdd::get_Name_na() const
{
    return ui->lineEdit_Name_na->text();
}

QString DialogAdd::get_Type_of_na() const
{
    return ui->lineEdit_Type_of_na->text();
}

QString DialogAdd::get_responsible_person() const
{
    return ui->lineEdit_Responsbile_person->text();
}


int DialogAdd::get_sal_of_r_p_who_make_a_doc() const
{
    return ui->spinBox_Salary->value();
}


int DialogAdd::get_aver_dev_time() const
{
    return ui->spinBox_Aver_dev_time->value();
}


int DialogAdd::get_min_amount_of_workers() const
{
    return ui->spinBoxMin_amount_of_workers->text().toInt();
}


void DialogAdd::on_pushButtonOK_clicked()
{
    clicked = "OK";
}


void DialogAdd::on_pushButtonCancel_clicked()
{
    clicked = "Cancel";
}


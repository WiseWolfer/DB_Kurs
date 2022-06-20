#include "dialogedit.h"
#include "ui_dialogedit.h"
#include "data_from_db.h"
#include <string>
#include <QString>
#include <iostream>

DialogEdit::DialogEdit(QWidget *parent) :
    QDialog(parent)
  ,ui(new Ui::DialogEdit)

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

DialogEdit::~DialogEdit()
{
    delete ui;
}


QString DialogEdit::get_Name_na() const
{
    return ui->lineEdit_Name_na->text();
}

void DialogEdit::show_Name_na(const QString &lName_na)
{
    ui->lineEdit_Name_na->setText(lName_na);
}

QString DialogEdit::get_Type_of_na() const
{
    return ui->lineEdit_Type_of_na->text();
}

void DialogEdit::show_Type_of_na(const QString &lType_of_na)
{
    ui->lineEdit_Type_of_na->insert(lType_of_na);
}

QString DialogEdit::get_responsible_person() const
{
    return ui->lineEdit_Responsbile_person->text();
}

void DialogEdit::show_responsible_person(const QString &lResponsible_person)
{
    ui->lineEdit_Responsbile_person->setText(lResponsible_person);
}

int DialogEdit::get_sal_of_r_p_who_make_a_doc() const
{
    return ui->spinBoxSalary->value();
}

void DialogEdit::show_sal_of_r_p_who_make_a_doc(const int &lSalary)
{
    ui->spinBoxSalary->setValue(lSalary);
}

int DialogEdit::get_aver_dev_time() const
{
    return ui->spinBox_Aver_dev_time->value();
}

void DialogEdit::show_aver_dev_time(const int &lavr_dev_time)
{
      ui->spinBox_Aver_dev_time->setValue(lavr_dev_time);
}

int DialogEdit::get_min_amount_of_workers() const
{
    return ui->spinBox_Min_amount_of_workers->value();
}

void DialogEdit::show_min_amount_of_workers(const int &lamount_of_workers)
{
     ui->spinBox_Min_amount_of_workers->setValue(lamount_of_workers);
}

void DialogEdit::on_pushButtonOK_clicked()
{
    clicked = "OK";
}


void DialogEdit::on_pushButton_Cancel_clicked()
{
    clicked = "Cancel";
}


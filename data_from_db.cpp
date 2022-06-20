#include "data_from_db.h"

Data_from_db::Data_from_db()
{

}

Data_from_db::~Data_from_db()
{

}

Data_from_db::Data_from_db(int lid, QString lName_na, QString lType_of_na,
                           QString lResponsible_person, int lSalary,
                           int lavr_dev_time, int lamount_of_workers):
   id(lid)
  ,Name_na(lName_na)
  ,Type_of_na(lType_of_na)
  ,Responsible_person(lResponsible_person)
  ,Salary(lSalary)
  ,aver_dev_time(lavr_dev_time)
  ,amount_of_workers(lamount_of_workers)
{

}

void Data_from_db::set_id(const int lid)
{
    id = lid;
}

int Data_from_db::get_id() const
{
    return id;
}

void Data_from_db::set_Name_na(const QString lName_na)
{
    Name_na = lName_na;
}

QString Data_from_db::get_Name_na() const
{
    return Name_na;
}

void Data_from_db::set_Type_of_na(const QString lType_of_na)
{
    Type_of_na = lType_of_na;
}

QString Data_from_db::get_Type_of_na() const
{
    return Type_of_na;
}

void Data_from_db::set_responsbile_person(const QString lResponsible_person)
{
    Responsible_person = lResponsible_person;
}

QString Data_from_db::get_responsible_person() const
{
    return Responsible_person;
}

void Data_from_db::set_sal_of_r_p_who_make_a_doc(const int lSalary)
{
    Salary  = lSalary;
}

int Data_from_db::get_Sal_of_r_p_who_make_a_doc() const
{
    return Salary;
}

void Data_from_db::set_aver_dev_time(const int lavr_dev_time)
{
    aver_dev_time = lavr_dev_time;
}

int Data_from_db::get_aver_dev_time() const
{
    return aver_dev_time;
}

void Data_from_db::set_min_amount_of_workers(const int lamount_of_workers)
{
    amount_of_workers = lamount_of_workers;
}

int Data_from_db::get_min_amount_of_workers() const
{
    return amount_of_workers;
}

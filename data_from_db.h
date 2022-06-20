#ifndef DATA_FROM_DB_H
#define DATA_FROM_DB_H

#include <QString>

///
/// \brief Класс The Data_from_db class - класс для взаимодействия с данными из БД
///


class Data_from_db
{
public:

    ///Конструктор класса
    Data_from_db();

    /// Деструктор класса
    ~Data_from_db();

    /// Конструктор с параметрами
    Data_from_db(int lid, QString lName_na, QString lType_of_na,
                 QString lResponsible_person, int lSalary,
                 int lavr_dev_time, int lamount_of_workers);

    /// Метод задает номер документа
    void set_id(const int lid);
    /// Метод возвращает номер доукмента
    int get_id() const;

    /// Метод задает названия документа
    void set_Name_na(const QString lName_na);
    /// Метод возвращает название документа
    QString get_Name_na() const;

    /// Метод задает тип документа
    void set_Type_of_na(const QString lType_of_na);
    /// Метод возвращает типа документа
    QString get_Type_of_na() const;

    /// Метод задает ФИО ответственного лица за документ
    void set_responsbile_person(const QString lResponsible_person);
    /// Метод возвращает ФИО ответственного лица за документ
    QString get_responsible_person() const;

    /// Метод задает зарплату ответственного лица
    void set_sal_of_r_p_who_make_a_doc(const int lSalary);
    /// Метод возвращает зарплату ответственного лица
    int get_Sal_of_r_p_who_make_a_doc() const;

    /// Метод задает среднее время разработки документа в днях
    void set_aver_dev_time(const int lavr_dev_time);
    /// Метод возвращает среднее время разработки документа в днях
    int get_aver_dev_time() const;

    /// Метод задает минимальное кол-во человек для разработки документа
    void set_min_amount_of_workers(const int lamount_of_workers);
    /// Метод возвращает минимальное кол-во человек для разработки документа
    int get_min_amount_of_workers() const;

private:
    ///  Номер документа
    int id;
    /// Названия документа
    QString Name_na;
    /// Тип документа
    QString Type_of_na;
    /// ФИО ответственного лица за документ
    QString Responsible_person;
    /// Зарплата ответственного лица
    int Salary;
    /// Среднее время разработки документа в днях
    int aver_dev_time;
    ///  Минимальное кол-во человек для разработки документа
    int amount_of_workers;
};

#endif // DATA_FROM_DB_H

#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
class DialogEdit;
}

using namespace std;


///
/// \brief Класс диалогового окна The DialogEdit class для удаления и редактирования данных.
///

class DialogEdit: public QDialog
{
    Q_OBJECT

public:
    /// Конструктор диалогового окна
    explicit DialogEdit(QWidget *parent = nullptr);
    /// Деструктор диалогового окна
    ~DialogEdit();

    /// метод возвращающий имя документа из диалогового окна
    QString get_Name_na() const;
    void show_Name_na(const QString &lName_na);

    /// метод возвращающий тип документа из диалогового окна
    QString get_Type_of_na() const;
    void show_Type_of_na(const QString &lType_of_na );

    /// метод возвращающий ФИО ответственного лица из диалогового окна
    QString get_responsible_person() const;
    void show_responsible_person(const QString &lResponsible_person);

    /// метод возвращает зарплату ответственного лица из диалогового окна
    int get_sal_of_r_p_who_make_a_doc() const;
    void show_sal_of_r_p_who_make_a_doc(const int &lSalary);

    /// метод возвращает среднее время разработки документа из диалогового окна
    int get_aver_dev_time() const;
    void show_aver_dev_time(const int &lavr_dev_time);

    /// метод возвращает минимальное кол-во работников для разработки документа из диалогового окна
    int get_min_amount_of_workers() const;
    void show_min_amount_of_workers(const int &lamount_of_workers);

    /// проработка кнопок OK и Cancel
    QString clicked;

private slots:

    void on_pushButtonOK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    /// указатель на диалоговое окно
    Ui::DialogEdit *ui;
    ///объявление переменных валидаторов
    QRegExpValidator val_name_of_na, val_type_of_na, val_resp_person;
};

#endif // DIALOGEDIT_H

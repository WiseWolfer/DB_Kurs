#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include <QRegExpValidator>


namespace Ui {
class DialogAdd;
}

using namespace std;

///
/// \brief Класс диалогового окна The DialogAdd class для удаления и редактирования данных.
///

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = nullptr);
    ~DialogAdd();

    /// проработка кнопок OK и Cancel
    QString clicked;

    /// метод возвращающий имя документа из диалогового окна
    QString get_Name_na() const;

    /// метод возвращающий тип документа из диалогового окна
    QString get_Type_of_na() const;

    /// метод возвращающий ФИО ответственного лица из диалогового окна
    QString get_responsible_person() const;

    /// метод возвращает зарплату ответственного лица из диалогового окна
    int get_sal_of_r_p_who_make_a_doc() const;

    /// метод возвращает среднее время разработки документа из диалогового окна
    int get_aver_dev_time() const;

    /// метод возвращает минимальное кол-во работников для разработки документа из диалогового окна
    int get_min_amount_of_workers() const;


private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogAdd *ui;
    ///объявление переменных валидаторов
    QRegExpValidator val_name_of_na, val_type_of_na, val_resp_person;
};

#endif // DIALOGADD_H

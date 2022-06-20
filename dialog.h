#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QRegExpValidator>


namespace Ui {
class Dialog;
}

///
/// \brief Класс The Dialog class - реализация класса диалогового окна для авторизации в БД
///

class Dialog : public QDialog
{
    Q_OBJECT

public:
    /// Конструктор диалогового окна
    explicit Dialog(QWidget *parent = nullptr);
    /// Деструктор диалогового окна
    ~Dialog();
    /// Метод возвращает с LineEdit имя хоста
    QString getHost_name() const;
    /// Метод возвращает с LineEdit порт
    int getPort() const;
    /// Метод возвращает с LineEdit название базы данных
    QString getDatabasename() const;
    /// Метод возвращает с LineEdit логин
    QString getUsername() const;
    /// Метод возвращает с LineEdit пароль
    QString getPassword() const;


private:
    /// указатель на диалоговое окно
    Ui::Dialog *ui;

    ///объявление переменных валидаторов
    QRegExpValidator val_HOST_NAME, val_Port;
};

#endif // DIALOG_H

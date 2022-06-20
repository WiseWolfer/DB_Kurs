#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableviewmodel.h"
#include "data_from_db.h"

#include <QString>
#include <QKeyEvent>
#include <QSortFilterProxyModel>
#include <QTranslator>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QInputDialog>
#include <iostream>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// Предупреждающее объявление класса TableViewModel для взаимодействия с моделью через главное окно.
class TableViewModel;

///
/// \brief Класс Главного окна - The MainWindow class
///

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Конструктор главного окна
    MainWindow(QWidget *parent = nullptr);
    /// Деструктор главного окна
    ~MainWindow();

    /// Метод для записи настроек окна
    void writesettings();

    ///Метод для сброса настроек окна
    void readsettings();

private slots:
    /// метод подключения к БД
    void on_actionConnect_triggered();

    /// метод вывода данных из бд
    void on_actionSelect_clicked();

    /// метод добавления новых данных в бд
    void on_actionAdd_data_triggered();

    /// метод обновления данных в бд
    void on_actionUpdate_data_triggered();

    /// метод удаления записи из бд
    void on_pushButtonDelete_data_clicked();

    /// метод вызывает диалоговое окно с информацией об авторе
    void on_actionAbout_the_author_triggered();

    /// метод вызывающая запись положения окна
    void on_actionAccept_window_size_triggered();

    /// метод вызывающая сброс размера окна
    void on_actionReset_window_size_triggered();

    /// метод поиска по названию
    void on_pushSearch_on_name_clicked();

    /// метод передает скопированный элемент ячейки tableview в lineEdit
    void take(QModelIndex r);

    /// метод переключения языка на русский
    void on_actionRussian_triggered();

    /// метод переключения языка на английский
    void on_actionEnglish_triggered();

    /// метод проверки смены языка и его перевода
    void changeEvent(QEvent *event);

private:
    /// указатель на главное окно
    Ui::MainWindow *ui;
    /// указатель на модель класса TableViewModel
    ///  для взаимодйствия с TableView
    TableViewModel *model;
    /// переменная проверка на нажатие определенной кнопки
    bool isClicked;
    /// указатель на класс QSortFilterProxyModel
    /// для создания proxymodel
    QSortFilterProxyModel *proxyModel;
    /// Создания объекта класса QTranslator
    /// для осуществления переводов
    QTranslator qtLanguageTranslator;
    /// Создание объекта класса  QSqlDatabase для транзакций и подключений к ДБ
    QSqlDatabase db;

};
#endif // MAINWINDOW_H

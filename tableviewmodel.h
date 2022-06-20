#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QAbstractTableModel>
#include "data_from_db.h"
#include <QModelIndex>

///
/// \brief Класс The TableViewModel class - класс модели tableview. С помощью него происходит взаимодействие с моделью.
///


class TableViewModel: public QAbstractTableModel
{
     Q_OBJECT
public:

    /// Конструктор TableViewModel(класса модели)
    explicit TableViewModel(QObject *parent=nullptr);
    /// Метод возвращает число записей в tableview
    int rowCount(const QModelIndex &parent) const override;
    /// Метод возвращает число столбцов в tableview
    int columnCount(const QModelIndex &parent) const override;
    /// Метод отображения данных в tableview из QList
    QVariant data(const QModelIndex &index, int role) const override;
    /// Метод добавлеия данных в QList, чтобы потом передать данные в tableview
    void add_data(const Data_from_db &newValues);
    /// Метод очистки QList
    void clear_data();

private:
     /// Контеннер для хранения данных из БД
      QList<Data_from_db> db;
      ///кол-во строк записей(порций) для вывода на экран
      int rows;
      // QAbstractItemModel interface
public:
      /// Метод задания заголовков столбцов в tableview
      QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


      // QAbstractItemModel interface
public:
      /// Метод подгрузки данных из бд по частям
      void fetchMore(const QModelIndex &parent) override;
      /// Метод проверки можно ли подгрузить еще записи из БД
      bool canFetchMore(const QModelIndex &parent) const override;
};

#endif // TABLEVIEWMODEL_H

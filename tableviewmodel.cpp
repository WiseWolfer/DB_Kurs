#include "tableviewmodel.h"
#include "mainwindow.h"
#include <QString>
#include "data_from_db.h"

#include <QList>
#include <QDebug>



TableViewModel::TableViewModel(QObject *parent)
     : QAbstractTableModel(parent)
     , rows(15)
{

}

int TableViewModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid()? 0 : rows;
}

int TableViewModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 7;
}

QVariant TableViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();

    if (row >= db.count() || row < 0)
        return QVariant();

    QVariant value;
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
        {
            value = db.at(index.row()).get_id();
            break;
        }
        case 1:
        {
            value = db.at(index.row()).get_Name_na();
            break;
        }
        case 2:
        {
            value = db.at(index.row()).get_Type_of_na();
            break;
        }
        case 3:
        {
            value = db.at(index.row()).get_responsible_person();
            break;
        }
        case 4:
        {
            value = db.at(index.row()).get_Sal_of_r_p_who_make_a_doc();
            break;
        }
        case 5:
        {
            value = db.at(index.row()).get_aver_dev_time();
            break;
        }
        case 6:
        {
            value = db.at(index.row()).get_min_amount_of_workers();
            break;
        }

        default:
                 break;
        }

      }
    return value;
}

void TableViewModel::add_data(const Data_from_db &newValues)
{
    beginResetModel();

    db.append(newValues);

    endResetModel();
}

void TableViewModel::clear_data()
{
    beginResetModel();

    db.clear();

    endResetModel();
}

QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
         switch (section) {
         case 0:
             return QString(tr("ID"));
         case 1:
             return QString(tr("Name of na"));
         case 2:
             return QString(tr("Type of na"));
         case 3:
             return QString(tr("Responsible person"));
         case 4:
             return QString(tr("Salary"));
         case 5:
             return QString(tr("Average dev.time"));
         case 6:
             return QString(tr("Minimal amount of workers"));
         }
     }
    return QVariant();
}

void TableViewModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
        return;

    qDebug() << "Fetch more";

    const int start = rows;
    const int remainder = db.count() - start;
    const int itemsToFetch = qMin(15, remainder);

    if (itemsToFetch <= 0)
        return;
    beginInsertRows(QModelIndex(), start, start + itemsToFetch - 1);

    rows += itemsToFetch;

    endInsertRows();
}

bool TableViewModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return false;
    }
    qDebug() << "Can fetch more";
    return (rows < db.count());
}







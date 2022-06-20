#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "tableviewmodel.h"
#include "dialogabout.h"
#include "dialogadd.h"
#include "dialogedit.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(QSqlDatabase::isDriverAvailable("QPSQL"))

        qDebug() << "Success!";
    else
        qDebug() << "Failure!";

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model = new TableViewModel(this);
    proxyModel = new QSortFilterProxyModel; //создаём и выделяем память объекту прокси модели
    ui->tableView->setSortingEnabled(true);
    readsettings();
    // подлкючение считывание сигнала по клику на ячейку в слот (в метод take())
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)),this, SLOT(take(QModelIndex)));
    isClicked = true;

    ui->actionConnect->setEnabled(isClicked);
    ui->actionAdd_data->setEnabled(!isClicked);
    ui->actionSelect->setEnabled(!isClicked);
    ui->pushButtonDelete_data->setEnabled(!isClicked);
    ui->actionUpdate_data->setEnabled(!isClicked);
    ui->pushSearch_on_name->setEnabled(!isClicked);

}


MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete proxyModel;
}


void MainWindow::on_actionConnect_triggered()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    isClicked = true;
    Dialog d;
    d.setWindowIcon(QIcon("C:/Users/Dmitriy/qt_programs/DB_Kurs/images/connect.png"));
    d.setMaximumHeight(200);
    d.setMinimumWidth(500);
    d.setMaximumWidth(600);
    d.exec();
    db.setHostName(d.getHost_name());
    db.setPort(d.getPort());
    db.setDatabaseName(d.getDatabasename());
    db.setUserName(d.getUsername());
    db.setPassword(d.getPassword());
    // включает PostgreSQL SSL соединения
    db.setConnectOptions("requiressl=1");
    db.open();
    if(!db.isOpen()){
        db.setConnectOptions(); // clear options
        QMessageBox::warning(this, tr("Application"), db.lastError().text());
        return;
    }
    else{
        ui->statusbar->showMessage("Success");
    }

    ui->actionAdd_data->setEnabled(!isClicked);
    ui->actionConnect->setEnabled(!isClicked);
    ui->actionSelect->setEnabled(isClicked);
    ui->pushButtonDelete_data->setEnabled(!isClicked);
    ui->actionUpdate_data->setEnabled(!isClicked);

}


void MainWindow::on_actionSelect_clicked()
{
    model->clear_data();
    QSqlQuery query;
    QString query_two_tables = "Select \"ID_na\", \"Name_na\", \"Type_of_na\", \"Responsible_person\", \"Sal_of_r_p_who_make_a_doc\","
"\"Aver_dev_time\", \"Min_amount_of_workers\" from intangible_assets, na_info where \"ID_na\" = \"ID_info\" Order by \"ID_info\" ASC;";

    bool ok = query.exec(query_two_tables);
    if(!ok){
        QMessageBox::critical(this, tr("Application"),query.lastError().text());
        return;
    }
    Data_from_db ddata;
    while(query.next()){
         ddata.set_id(query.value(0).toInt());
         ddata.set_Name_na((query.value(1).toString()));
         ddata.set_Type_of_na((query.value(2).toString()));
         ddata.set_responsbile_person((query.value(3).toString()));
         ddata.set_sal_of_r_p_who_make_a_doc((query.value(4).toInt()));
         ddata.set_aver_dev_time((query.value(5).toInt()));
         ddata.set_min_amount_of_workers((query.value(6).toInt()));

         model->add_data(Data_from_db(ddata.get_id(), ddata.get_Name_na(),
                                      ddata.get_Type_of_na(), ddata.get_responsible_person(),
                                      ddata.get_Sal_of_r_p_who_make_a_doc(), ddata.get_aver_dev_time(),
                                      ddata.get_min_amount_of_workers()));

    }
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    ui->actionConnect->setEnabled(!isClicked);
    ui->actionAdd_data->setEnabled(isClicked);
    ui->actionSelect->setEnabled(!isClicked);
    ui->pushButtonDelete_data->setEnabled(isClicked);
    ui->actionUpdate_data->setEnabled(isClicked);
    ui->pushSearch_on_name->setEnabled(isClicked);
}


void MainWindow::on_actionAdd_data_triggered()
{
  DialogAdd dialog;
  dialog.setWindowIcon(QIcon("C:/Users/Dmitriy/qt_programs/DB_Kurs/images/add_data.png"));
  dialog.setMaximumHeight(300);
  dialog.setMinimumWidth(500);
  dialog.setMaximumWidth(600);
  dialog.exec();

  QSqlQuery query, query1, query2;
  Data_from_db ddata;
  ddata.set_Name_na(dialog.get_Name_na());
  ddata.set_Type_of_na(dialog.get_Type_of_na());
  ddata.set_responsbile_person(dialog.get_responsible_person());
  ddata.set_sal_of_r_p_who_make_a_doc(dialog.get_sal_of_r_p_who_make_a_doc());
  ddata.set_aver_dev_time(dialog.get_aver_dev_time());
  ddata.set_min_amount_of_workers(dialog.get_min_amount_of_workers());

  query.exec("SELECT Max(\"ID_na\") FROM intangible_assets");
  int id = 0;
  while(query.next()){
    id = query.value(0).toInt();
   }
  QString button = dialog.clicked;
  if(button != "OK"){
      return;
  }

    db.transaction(); // Начало транзацкции
    query1.prepare("INSERT INTO intangible_assets(\"ID_na\", \"Name_na\", \"Type_of_na\") VALUES(?, ?, ?)");
    query1.addBindValue(id+1);
    query1.addBindValue(dialog.get_Name_na());
    query1.addBindValue(dialog.get_Type_of_na());

    query2.prepare("INSERT INTO na_info(\"ID_info\", \"Responsible_person\", \"Sal_of_r_p_who_make_a_doc\", "
    "\"Aver_dev_time\", \"Min_amount_of_workers\") VALUES (?, ?, ?, ?, ?)");
    query2.addBindValue(id+1);
    query2.addBindValue(dialog.get_responsible_person());
    query2.addBindValue(dialog.get_sal_of_r_p_who_make_a_doc());
    query2.addBindValue(dialog.get_aver_dev_time());
    query2.addBindValue(dialog.get_min_amount_of_workers());

    bool ok = query1.exec();
    bool ok1 = query2.exec();

    if((query1.lastError().type() != QSqlError::NoError and query2.lastError().type() != QSqlError::NoError) || (!ok and !ok1)){
    qDebug() << query.lastError().text()<<"\n";
    qDebug() <<"Inserted unsuccessfully"<<"\n";
    db.rollback(); // Откат транзакции
    QMessageBox::critical(this, tr("Application"),query1.lastError().text(),query2.lastError().text());
    return;
    }
    qDebug() <<"Inserted successfully"<<"\n";
    db.commit(); // Конец транзацкции


    model->add_data(Data_from_db(id +1,ddata.get_Name_na(),
      ddata.get_Type_of_na(), ddata.get_responsible_person(),
      ddata.get_Sal_of_r_p_who_make_a_doc(), ddata.get_aver_dev_time(),
      ddata.get_min_amount_of_workers()));

    on_actionSelect_clicked();

  ui->actionConnect->setEnabled(!isClicked);
  ui->actionSelect->setEnabled(!isClicked);
}

// Метод Редактирования записи из бд
/*
   Работает следующим образом:
    1) Выделяем всю строку с имзеняемыми данными
    2) Жмем Редактировать -> редактировать данные
    3) В диалоговом окне видим считанные данные, меняем их на новые
    4) Жмем ок, если хотим, чтобы редактируемая запись появилась в tableview и БД
    5) Жмем cancel или крестик, чтобы не изменять запись
*/

void MainWindow::on_actionUpdate_data_triggered()
{
    QSqlQuery query, query1, query3;
    DialogEdit dialog;
    dialog.setWindowIcon(QIcon("C:/Users/Dmitriy/qt_programs/DB_Kurs/images/update_data.png"));
    dialog.setMaximumHeight(300);
    dialog.setMinimumWidth(550);
    dialog.setMaximumWidth(600);
    QModelIndexList l = ui->tableView->selectionModel()->selectedRows();
    if(l.isEmpty()) return;

    query3.prepare("Select \"Name_na\", \"Type_of_na\", \"Responsible_person\", \"Sal_of_r_p_who_make_a_doc\","
"\"Aver_dev_time\", \"Min_amount_of_workers\" from intangible_assets, na_info where \"ID_na\" = \"ID_info\" and \"ID_info\" = ? Order by \"ID_info\" ASC;");
    query3.addBindValue(l[0].row()+1);
    query3.exec();
    while (query3.next()) {
        dialog.show_Name_na(query3.value(0).toString());
        dialog.show_Type_of_na(query3.value(1).toString());
        dialog.show_responsible_person(query3.value(2).toString());
        dialog.show_sal_of_r_p_who_make_a_doc(query3.value(3).toInt());
        dialog.show_aver_dev_time(query3.value(4).toInt());
        dialog.show_min_amount_of_workers(query3.value(5).toInt());
    }

    dialog.exec();

    QString button = dialog.clicked;
    if(button != "OK"){
        return;
    }

    Data_from_db ddata;
    ddata.set_Name_na(dialog.get_Name_na());
    ddata.set_Type_of_na(dialog.get_Type_of_na());
    ddata.set_responsbile_person(dialog.get_responsible_person());
    ddata.set_sal_of_r_p_who_make_a_doc(dialog.get_sal_of_r_p_who_make_a_doc());
    ddata.set_aver_dev_time(dialog.get_aver_dev_time());
    ddata.set_min_amount_of_workers(dialog.get_min_amount_of_workers());

    db.transaction(); // Начало транзацкции

    query.prepare("Update intangible_assets SET \"Name_na\" = ?, \"Type_of_na\" = ? where \"ID_na\" = ?");
    query.bindValue(0, ddata.get_Name_na());
    query.bindValue(1, ddata.get_Type_of_na());
    query.bindValue(2, l[0].row()+1);

    query1.prepare("Update na_info SET \"Responsible_person\" = ?,"
" \"Sal_of_r_p_who_make_a_doc\" = ?, \"Aver_dev_time\" = ?, \"Min_amount_of_workers\" = ? where \"ID_info\" = ? ");

    query1.bindValue(0, ddata.get_responsible_person());
    query1.bindValue(1, ddata.get_Sal_of_r_p_who_make_a_doc());
    query1.bindValue(2, ddata.get_aver_dev_time());
    query1.bindValue(3, ddata.get_min_amount_of_workers());
    query1.bindValue(4, l[0].row()+1);

    bool ok = query.exec();
    bool ok1 = query1.exec();
    if((query.lastError().type() != QSqlError::NoError and query1.lastError().type() != QSqlError::NoError) || (!ok and !ok1)){
        qDebug() << query.lastError().text();
        db.rollback(); // Откат транзакции
        qDebug() << "Deleted unsuccessfully" <<"\n";
        QMessageBox::critical(this, tr("Application"),query.lastError().text(),query1.lastError().text());
        return;
    }
    db.commit(); // Конец транзацкции

    on_actionSelect_clicked();
    ui->actionConnect->setEnabled(!isClicked);
    ui->actionSelect->setEnabled(!isClicked);
}


void MainWindow::on_pushButtonDelete_data_clicked()
{
    QSqlQuery query;
    QString val = ui->lineEditDelete->text();

    db.transaction(); // Начало транзакции
    query.prepare("DELETE FROM intangible_assets WHERE \"Name_na\" = :val;");
    query.bindValue(":val",val);
    bool ok = query.exec();

    if((query.lastError().type() != QSqlError::NoError) || !ok )
    {
        qDebug() << query.lastError().text() <<"\n";
        qDebug() << "Deleted unsuccessfully" <<"\n";
        db.rollback(); // Откат транзакции
        QMessageBox::critical(this, tr("Application"),
                             query.lastError().text());
        return;
   }
   db.commit(); // Конец транзакции
   qDebug() << "Deleted successfully" <<"\n";
   on_actionSelect_clicked();
   ui->actionConnect->setEnabled(!isClicked);
   ui->actionSelect->setEnabled(!isClicked);
}


void MainWindow::on_actionAbout_the_author_triggered()
{
    ///Здесь будет происходить вызов диалогового окна об авторе
    DialogAbout about;
    about.setWindowIcon(QIcon("C:/Users/Dmitriy/qt_programs/DB_Kurs/images/about.png"));
    about.setWindowTitle(tr("About author"));
    about.setMaximumHeight(100);
    about.setMinimumWidth(300);
    about.setMaximumWidth(400);
    about.exec();
}


void MainWindow::writesettings()
{
    QSettings settings("My Program");
   //созданиие настроек окна для записи
    settings.beginGroup("MainWindowGeometry");
   //запись размера
    settings.setValue("size",size());
    //запись позиции
    settings.setValue("position",pos());
    settings.endGroup();
}


void MainWindow::readsettings()
{
    QSettings settings("My Program");
    settings.beginGroup("MainWindowGeometry");

    resize(settings.value("size", QSize(400, 400)).toSize());    //сбрасываем размер окна
    move(settings.value("position", QPoint(200, 200)).toPoint()); //сбрасываем крайнюю левую точку
    settings.setValue("position",pos()); //устанавливам текущую позицию
    settings.endGroup();
}


void MainWindow::on_actionAccept_window_size_triggered()
{
    // меняем размер окна нажимаем и перезапускаем окно, сохранив последнее положение
    //создаем объект информационного окна qt и говорим пользователю о примененных настройках
    QMessageBox msgBox;
    msgBox.setWindowTitle("Применения настроек");
    msgBox.setText("Нажмите Ок  и изменения вступят в силу");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    writesettings();
}


void MainWindow::on_actionReset_window_size_triggered()
{
    // меняем размеры окна руками а потом жмем на кнопку сброса
    QMessageBox msgBox;
    msgBox.setWindowTitle("Применения настроек");
    msgBox.setText("Нажмите Ок  и изменения вступят в силу");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    readsettings();
}


void MainWindow::on_pushSearch_on_name_clicked()
{
     QSqlQuery query;
     QString Name_na = ui->lineSearchName->text();
     query.prepare("Select \"ID_na\", \"Name_na\", \"Type_of_na\", \"Responsible_person\", \"Sal_of_r_p_who_make_a_doc\","
"\"Aver_dev_time\", \"Min_amount_of_workers\" from intangible_assets, na_info where \"ID_na\" = \"ID_info\" and \"Name_na\" like ? Order by \"ID_info\" ASC;");
     query.addBindValue(Name_na);
     query.exec();

     if (!query.exec()) {
        QMessageBox::critical(this, tr("Application"),
                              query.lastError().text());
        return;
    }
     model->clear_data();
     Data_from_db ddata;
     while(query.next()){
          ddata.set_id(query.value(0).toInt());
          ddata.set_Name_na((query.value(1).toString()));
          ddata.set_Type_of_na((query.value(2).toString()));
          ddata.set_responsbile_person((query.value(3).toString()));
          ddata.set_sal_of_r_p_who_make_a_doc((query.value(4).toInt()));
          ddata.set_aver_dev_time((query.value(5).toInt()));
          ddata.set_min_amount_of_workers((query.value(6).toInt()));

          model->add_data(Data_from_db(ddata.get_id(), ddata.get_Name_na(),
                                       ddata.get_Type_of_na(), ddata.get_responsible_person(),
                                       ddata.get_Sal_of_r_p_who_make_a_doc(), ddata.get_aver_dev_time(),
                                       ddata.get_min_amount_of_workers()));

     }
     proxyModel->setSourceModel(model);
     ui->tableView->setModel(proxyModel);
     ui->pushSearch_on_name->setEnabled(!isClicked);
     ui->pushButtonDelete_data->setEnabled(!isClicked);
     ui->actionUpdate_data->setEnabled(!isClicked);
     ui->actionAdd_data->setEnabled(!isClicked);
     ui->actionSelect->setEnabled(isClicked);

}


void MainWindow::take(QModelIndex r)
{
    ui->lineEditDelete->setText(ui->tableView->model()->data(r,Qt::DisplayRole).toString());

    ui->lineSearchName->setText(ui->tableView->model()->data(r,Qt::DisplayRole).toString());
}


void MainWindow::on_actionRussian_triggered()
{
    qApp->removeTranslator(&qtLanguageTranslator);
            qtLanguageTranslator.load(":/DB_Kurs_ru_RU");
            qApp->installTranslator(&qtLanguageTranslator);
}


void MainWindow::on_actionEnglish_triggered()
{
    qApp->removeTranslator(&qtLanguageTranslator);
            qtLanguageTranslator.load(":/DB_Kurs_en_US");
            qApp->installTranslator(&qtLanguageTranslator);
}


void MainWindow::changeEvent(QEvent *event)
{
    // Проверка смены языка
    if (event->type() == QEvent::LanguageChange) {
               ui->retranslateUi(this);    // переведём окно заново
           }
}


#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

///
/// \brief Класс The DialogAbout class для вывода информации о создателе программы.
///

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    /// Конструктор диалогового окна
    explicit DialogAbout(QWidget *parent = nullptr);
    /// Деструктор диалогового окна
    ~DialogAbout();

private:
    /// указатель на диалоговое окно
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H

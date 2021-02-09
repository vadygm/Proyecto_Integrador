#ifndef DIALOG_SAVE_H
#define DIALOG_SAVE_H

#include <QDialog>

namespace Ui {
class Dialog_Save;
}

class Dialog_Save : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Save(QWidget *parent = nullptr);
    ~Dialog_Save();

    char getDesitio() const;

private slots:
    void on_cm_Yes_clicked();
    void on_cm_No_clicked();
    void on_cm_Cancel_clicked();

private:
    Ui::Dialog_Save *ui;
    char desitio = 'c';
};

#endif // DIALOG_SAVE_H

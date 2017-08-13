#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDir>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_buttonBox_rejected();
    void handleScrollbar();

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;

    QDir installDir;
    bool bTextIsDown;
};

#endif // DIALOG_H

#include "dialog.h"
#include "ui_dialog.h"
#include <QDialogButtonBox>
#include <QScrollBar>
#include <QPushButton>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <fileapi.h>
#include <string>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->textBrowser->verticalScrollBar(), SIGNAL(actionTriggered(int)), this, SLOT(handleScrollbar()));

    bTextIsDown = false;
    for(int i = 1; i < ui->tabWidget->count(); i++)
        ui->tabWidget->setTabEnabled(i, false);
    ui->tabWidget->setCurrentIndex(0);
    ui->buttonBox->button(ui->buttonBox->Ok)->setEnabled(false);
}

void Dialog::handleScrollbar()
{
    if(ui->textBrowser->verticalScrollBar()->sliderPosition() >= 100)
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void Dialog::on_buttonBox_rejected()
{
    if(QMessageBox::warning(this, "...", "Exiting will cancel installation",
                             QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
    {
        QApplication::exit();
    }
}

void Dialog::on_buttonBox_accepted()
{
    if(ui->tabWidget->currentWidget() == ui->tab_2)
    {
        if(!QDir(ui->textEdit->toPlainText()).isReadable() ||
                !QFileInfo(ui->textEdit->toPlainText()).isDir())
        {
            QMessageBox::critical(this, "...", "The file path you entered was not valid, please choose another "
                                               "one anad try again", QMessageBox::Ok,
                                                                     QMessageBox::StandardButton());
            return;
        }
        else
        {
            installDir.setPath(ui->textEdit->toPlainText());
            std::cout << installDir.path().toStdString() << std::endl;
            ui->textBrowser_2->setText("File Location: " + installDir.path() +
                                       "\n\nPress OK to install. Wizard will close afterwards.");
        }
    }
    else if(ui->tabWidget->currentWidget() == ui->tab_3)
    {
        QString xd = installDir.path();

        qDebug() << xd;

        if(xd[xd.size() - 1] != '/')
            xd.append("/");

        qDebug() << xd;

        QFile file(xd + "xd.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(" ");
        file.close();
    }

    ui->tabWidget->setTabEnabled(ui->tabWidget->currentIndex() + 1, true);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
}

void Dialog::on_pushButton_clicked()
{
    ui->textEdit->setText(QFileDialog::getExistingDirectory(this, "Select installation directiory",
                                                      QDir::homePath(), QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks));
}

Dialog::~Dialog()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QThread>
#include <QSqlTableModel>
#include <QTableView>
#include "teacherview.h"
#include "studailog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QSqlDatabase db;
    teacherview tv;
    stuDailog sd;
    ~MainWindow();


private slots:
    void on_login_clicked();

signals:
    void sendData(QString);

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

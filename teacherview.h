#ifndef TEACHERVIEW_H
#define TEACHERVIEW_H

#include <QTableWidgetItem>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class teacherview;
}

class teacherview : public QWidget
{
    Q_OBJECT

public:
    explicit teacherview(QWidget *parent = 0);
    QSqlDatabase db;
    QString id;
    QString str;
    QStringList list;
    void getdb(QSqlDatabase db);
    void showEvent(QShowEvent *event);
    ~teacherview();

private slots:
    void on_showbutton_clicked();

    void on_update_clicked();

    void on_addbutton_clicked();

    void on_sortButton_clicked();

    void on_descendbutton_clicked();

    void on_deletebutton_clicked();

    void on_yearButton_clicked();

    void on_sidButton_clicked();

    void on_highButton_clicked();

    void on_lowButton_clicked();

    void on_showButton_clicked();

    void on_graghButton_clicked();

    void on_classbutton_clicked();

private:
    Ui::teacherview *ui;
};

#endif // TEACHERVIEW_H

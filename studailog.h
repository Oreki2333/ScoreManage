#ifndef STUDAILOG_H
#define STUDAILOG_H

#include <QDialog>


#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class stuDailog;
}

class stuDailog : public QDialog
{
    Q_OBJECT

public:
    explicit stuDailog(QWidget *parent = 0);
    void getdb(QSqlDatabase db);
         QSqlDatabase db;
    QString s_id;
    QString s_class;
    QString year;
    ~stuDailog();

private slots:
         void on_showStudentInfoButton_clicked();

         void on_Find_clicked();

private:
    Ui::stuDailog *ui;
};

#endif // STUDAILOG_H

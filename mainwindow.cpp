#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("QMainWindow{border-image:url(C:/Users/Oreki/Desktop/1/ScoreSystem/ScoreManagement/1.jpg)}");
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("baigei");
    db.setUserName("root");
    db.setPassword("123456");
    ui->pwd_lineedit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

//登陆操作
void MainWindow::on_login_clicked()
{
    //检查角色
    bool isTeacher = ui->radioButton->isChecked();
    bool isStudent = ui->radioButton_2->isChecked();
    QSqlQuery query(db);

    //如果是教师
    if(isTeacher)
    {
        query.prepare("select t_name from teacher where t_id= ? and t_pswd = ?");
        query.addBindValue(ui->user_lineedit->text());
        query.addBindValue(ui->pwd_lineedit->text());
        if(query.exec() && query.next())
        {
            this->hide();//隐藏登陆窗口
            tv.id=ui->user_lineedit->text();
            QString name = query.value(0).toString();
            QMessageBox::information(this,"提示","欢迎使用，"+name+"老师",QMessageBox::Ok);
            for(int i=90000000;i>0;i--);//等待一段时间
            tv.getdb(db);

            query.prepare("select c_name from teacher where t_id= ?");
            query.addBindValue(tv.id);
            query.exec();

            int i=0;
            while(query.next())
            {
                tv.list.insert(i,query.value(0).toString());
                i++;
            }
            //显示教师界面
            tv.show();
        }
        else{
             QMessageBox::warning(this,"Warning","用户名或者密码错误,请重新登陆");
        }
    }
    //如果是学生
    else if(isStudent)
    {
        query.prepare("select s_name from student where s_id = ?");
        query.addBindValue(ui->user_lineedit->text());
        emit sendData(ui->user_lineedit->text()); //获取lineEdit的输入并且传递出去
        if(query.exec() && query.next())
        {
            this->hide();//隐藏登陆窗口
            sd.s_id=ui->user_lineedit->text();
            QString name = query.value(0).toString();
            QMessageBox::information(this,"提示","欢迎使用"+name+"同学",QMessageBox::Ok);
            for(int i=90000000;i>0;i--);//等待一段时间
            sd.getdb(db);
            //显示学生界面
            sd.show();
        }
        else{
             QMessageBox::warning(this,"warning","没有此学生重新登陆");
        }
    }
}
//用户身份————老师
void MainWindow::on_radioButton_clicked()
{
    this->ui->user_label->show();
    this->ui->pwd_label->show();
    this->ui->user_lineedit->show();
    this->ui->pwd_lineedit->show();

}
//用户身份————学生
void MainWindow::on_radioButton_2_clicked()
{
     this->ui->user_label->show();
     this->ui->pwd_label->hide();
     this->ui->user_lineedit->show();
     this->ui->pwd_lineedit->hide();

}

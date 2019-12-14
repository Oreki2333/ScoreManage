#include "studailog.h"
#include "ui_studailog.h"

stuDailog::stuDailog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stuDailog)
{
    ui->setupUi(this);
    setStyleSheet("QDialog{border-image:url(C:/Users/Oreki/Desktop/1/ScoreSystem/ScoreManagement/2.jpg)}");
    // 以行作为选择标准
    ui->tableView_student->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);
    // 列头灰色
    ui->tableView_student->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(0,0,0,0)};");
    ui->tableView_student->setStyleSheet("background-color:rgba(0,0,0,0)");
}

stuDailog::~stuDailog()
{
    delete ui;
}
void stuDailog::getdb(QSqlDatabase db)
{
    this->db = db;

}
//显示当前登陆学生成绩
void stuDailog::on_showStudentInfoButton_clicked()
{
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    ui->tableView_student->setModel(pModel);
    pModel->setTable("grades");
    QString filter="s_id="+s_id;

    pModel->setFilter(filter);
    pModel->setHeaderData(0, Qt::Horizontal, "学号");
    pModel->setHeaderData(1, Qt::Horizontal, "姓名");
    pModel->setHeaderData(2, Qt::Horizontal, "班级");
    pModel->setHeaderData(3, Qt::Horizontal, "教师号");
    pModel->setHeaderData(4, Qt::Horizontal, "课程名");
    pModel->setHeaderData(5, Qt::Horizontal, "学年");
    pModel->setHeaderData(6, Qt::Horizontal, "成绩");
    pModel->select();
}
//显示统计信息
void stuDailog::on_Find_clicked()
{
    //获取所在班级
    QString c=ui->lineEdit->text();
    QSqlQuery query;
    query.prepare("select s_class from grades where s_id= ? and c_name= ?");
    query.addBindValue(s_id);
    query.addBindValue(c);
    query.exec();
    query.next();
    s_class=query.value(0).toString();
    ui->lineEdit_3->setText(s_class);

    //显示表单
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    ui->tableView_student->setModel(pModel);
    pModel->setTable("grades");
    QString filter="c_name ='%1'&& s_class ="+s_class;
    pModel->setFilter(filter.arg(c));
    pModel->setHeaderData(0, Qt::Horizontal, "学号");
    pModel->setHeaderData(1, Qt::Horizontal, "姓名");
    pModel->setHeaderData(2, Qt::Horizontal, "班级");
    pModel->setHeaderData(3, Qt::Horizontal, "教师号");
    pModel->setHeaderData(4, Qt::Horizontal, "课程名");
    pModel->setHeaderData(5, Qt::Horizontal, "学年");
    pModel->setHeaderData(6, Qt::Horizontal, "成绩");
    pModel->select();

    //显示统计值
    query.prepare("select max(score) maxScore,min(score) minScore,avg(score) avgScore from grades where c_name= ? and s_class= ?");
    query.addBindValue(c);
    query.addBindValue(s_class);
    query.exec();
    query.next();
    ui->Max->setText(query.value(0).toString());
    ui->Min->setText(query.value(1).toString());
    ui->Avg->setText(QString::number(query.value(2).toInt()));

    //显示排名
    int count=0;
    query.prepare("select s_id,score from grades where c_name= ? and s_class= ? order by score desc");
    query.addBindValue(c);
    query.addBindValue(s_class);
    while(query.exec()&&query.next())
    {
        count++;
        if(query.value(0).toString()==s_id)
            break;
    }
    ui->lineEdit_4->setText(QString::number(count));
}

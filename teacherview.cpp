#include "teacherview.h"
#include "ui_teacherview.h"

#include "hehe.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

teacherview::teacherview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherview)
{
    ui->setupUi(this);
    // 以行作为选择标准
    ui->tableView->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);
    // 列头灰色
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");

}
teacherview::~teacherview()
{
    delete ui;
}
//下拉列表数据更新
void teacherview::showEvent(QShowEvent *event)
{
    for(int i=0;i!=list.size();i++)
        ui->comboBox->addItem(list[i]);
    QWidget::showEvent(event);
}
//获取数据库
void teacherview::getdb(QSqlDatabase db)
{
    this->db = db;
}
//学年查询
void teacherview::on_yearButton_clicked()
{
    QString find=this->ui->findlineedit->text();
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    QString filter = "year ="+find+"&& t_id ="+id;

    ui->tableView->setModel(pModel);
    pModel->setTable("grades");

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
//学号查询
void teacherview::on_sidButton_clicked()
{
    QString find=this->ui->findlineedit->text();
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    QString filter = "s_id ="+find+"&& t_id ="+id;

    ui->tableView->setModel(pModel);
    pModel->setTable("grades");

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
//班级查询
void teacherview::on_classbutton_clicked()
{
    QString find=this->ui->findlineedit->text();
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    QString filter = "s_class ="+find+"&& t_id ="+id;

    ui->tableView->setModel(pModel);
    pModel->setTable("grades");

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
//显示信息
void teacherview::on_showbutton_clicked()
{
    str=ui->comboBox->currentText();
    QSqlTableModel *pModel = new QSqlTableModel(this, db);
    ui->tableView->setModel(pModel);
    pModel->setTable("grades");

    QString filter="c_name = '%1' && t_id ="+id;
    pModel->setFilter(filter.arg(str));
    pModel->setHeaderData(0, Qt::Horizontal, "学号");
    pModel->setHeaderData(1, Qt::Horizontal, "姓名");
    pModel->setHeaderData(2, Qt::Horizontal, "班级");
    pModel->setHeaderData(3, Qt::Horizontal, "教师号");
    pModel->setHeaderData(4, Qt::Horizontal, "课程名");
    pModel->setHeaderData(5, Qt::Horizontal, "学年");
    pModel->setHeaderData(6, Qt::Horizontal, "成绩");
    pModel->select();

}
//更新操作
void teacherview::on_update_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    pMode->database().transaction(); //开始事务操作
    if (pMode->submitAll()) // 提交所有被修改的数据到数据库中
    {
        pMode->database().commit(); //提交成功，事务将真正修改数据库数据
    } else {
        pMode->database().rollback(); //提交失败，事务回滚
        QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pMode->lastError().text()));
    }
    pMode->revertAll(); //撤销修改
}
//增加操作
void teacherview::on_addbutton_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());

    QString text= this->ui->addbutton->text();
    if(text==QString("添加"))
    {
        pMode->insertRow(pMode->rowCount(QModelIndex()));
        this->ui->addbutton->setText(QString("保存"));
    }
    else if(text==QString("保存"))
    {
        this->ui->addbutton->setText(QString("添加"));
        pMode->database().transaction(); //开始事务操作
        if (pMode->submitAll()) // 提交所有被修改的数据到数据库中
        {
            pMode->database().commit(); //提交成功，事务将真正修改数据库数据
        } else {
            pMode->database().rollback(); //提交失败，事务回滚
            QMessageBox::warning(this, tr("tableModel"),tr("数据库错误: %1").arg(pMode->lastError().text()));
        }
        pMode->revertAll(); //撤销修改
    }


}
//删除操作
void teacherview::on_deletebutton_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    // 当QSqlTableModel::EditStrategy 选择 非QSqlTableModel::OnManualSubmit 时,
    // 每次删除都可删除掉model，但是tableview那一列为空，一直在，只好设置为 QSqlTableModel::OnManualSubmit
    pMode->removeRow(ui->tableView->currentIndex().row());
    // 每次手动提交，都会重新刷新tableView，保持mode和tableView一致
    pMode->submitAll();
}
//学号升序显示
void teacherview::on_sortButton_clicked()
{
     QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
     pMode->sort(0, Qt::AscendingOrder); // 第0列升序排序
}
//学号降序显示
void teacherview::on_descendbutton_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    pMode->sort(0,Qt::DescendingOrder);
}
//成绩升序显示
void teacherview::on_highButton_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    pMode->sort(6, Qt::AscendingOrder); // 第0列升序排序
}
//成绩降序显示
void teacherview::on_lowButton_clicked()
{
    QSqlTableModel *pMode = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    pMode->sort(6,Qt::DescendingOrder);
}
//数学统计值
void teacherview::on_showButton_clicked()
{
    str=ui->comboBox->currentText();
    QSqlQuery query;
    query.exec(QString("select max(score) maxScore,min(score) minScore,avg(score) avgScore from grades where year= '%1' and t_id= '%2' and c_name = '%3'").arg(ui->findlineedit->text()).arg(id).arg(str));
    query.next();

    ui->maxlineedit->setText(query.value(0).toString());
    ui->minlineedit->setText(query.value(1).toString());
    ui->avglineedit->setText(QString::number(query.value(2).toInt()));
}
//统计绘图
void teacherview::on_graghButton_clicked()
{
    hehe *h=new hehe();
    //创建柱
    QBarSet *set0 = new QBarSet("最高分");
    QBarSet *set1 = new QBarSet("最低分");
    QBarSet *set2 = new QBarSet("平均分");
    //柱属性
    set0->setLabelColor(QColor(10,10,10));
    set1->setLabelColor(QColor(10,10,10));
    set2->setLabelColor(QColor(10,10,10));
    //柱数据
    str=ui->comboBox->currentText();
    QSqlQuery query;
    query.exec(QString("select max(score) maxScore,min(score) minScore,avg(score) avgScore from grades where year= 2017 and t_id= '%1' and c_name = '%2'").arg(id).arg(str));
    query.next();
    double max_2017=query.value(0).toDouble();
    double min_2017=query.value(1).toDouble();
    double avg_2017=query.value(2).toDouble();

    query.exec(QString("select max(score) maxScore,min(score) minScore,avg(score) avgScore from grades where year= 2018 and t_id= '%1' and c_name = '%2'").arg(id).arg(str));
    query.next();
    double max_2018=query.value(0).toDouble();
    double min_2018=query.value(1).toDouble();
    double avg_2018=query.value(2).toDouble();

    query.exec(QString("select max(score) maxScore,min(score) minScore,avg(score) avgScore from grades where year= 2019 and t_id= '%1' and c_name = '%2'").arg(id).arg(str));
    query.next();
    double max_2019=query.value(0).toDouble();
    double min_2019=query.value(1).toDouble();
    double avg_2019=query.value(2).toDouble();
    //添加数据
    *set0<<max_2017<<max_2018<<max_2019;
    *set1<<min_2017<<min_2018<<min_2019;
    *set2<<avg_2017<<avg_2018<<avg_2019;
    //创建柱状图
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    series->setVisible(true);//设置条形图是否可视化
    series->setBarWidth(0.8);//设置Bar宽
    series->setLabelsVisible(true);//设置标签是否可视化
    series->setLabelsAngle(30);//设置标签的角度
    series->setLabelsFormat("@value");//设置标签显示的格式
    series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);//设置标签的位置
    series->setLabelsPrecision(5);//标签中显示的最大有效位数

    QChart *chart = new QChart();
    chart->setTitle("近三年学生成绩统计");
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
    chart->setLocalizeNumbers(true);//数字是否本地化
    chart->createDefaultAxes();//创建默认轴
    chart->setTitleBrush(QBrush(QColor(10,10,10)));//设置标题Brush
    chart->setTitleFont(QFont("微软雅黑"));//设置标题字体

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignTop);//对齐
    chart->legend()->setLabelColor(QColor(10,10,10));//设置标签颜色
    chart->legend()->setVisible(true);//设置是否可视
    chart->legend()->setBorderColor(QColor(255,255,170,185));//设置边框颜色
    QFont font = chart->legend()->font();
    font.setItalic(!font.italic());
    chart->legend()->setFont(font);//设置字体为斜体
    font.setPointSizeF(12);
    chart->legend()->setFont(font);//设置字体大小
    chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型

    QStringList categories;
    categories << "2017" << "2018" << "2019" ;
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->setAxisX(axis, series);//设置X轴
    //X轴
    chart->axisX(series)->setVisible(true);
    chart->axisX(series)->setRange(2000,2050);//设置X轴范围
    //X轴标题
    chart->axisX(series)->setTitleText("年份（年）");//设置X轴标题
    chart->axisX(series)->setTitleBrush(QBrush(QColor(10,10,10)));
    chart->axisX(series)->setTitleFont(QFont("微软雅黑"));
    chart->axisX(series)->setTitleVisible(true);
    //X轴网格
    chart->axisX(series)->setGridLineColor(QColor(10,10,10));//设置X轴网格线颜色
    chart->axisX(series)->setGridLineVisible(true);
    //X轴标签
    chart->axisX(series)->setLabelsAngle(30);
    chart->axisX(series)->setLabelsColor(QColor(10,10,10));
    chart->axisX(series)->setLabelsFont(QFont("Arial"));
    chart->axisX(series)->setLabelsVisible(true);
    //X轴轴线
    chart->axisX(series)->setLinePenColor(QColor(10,10,10));
    chart->axisX(series)->setLineVisible(true);

    //Y轴
    chart->axisY(series)->setVisible(true);
    chart->axisY(series)->setRange(0,100);//设置Y轴范围
    //Y轴标题
    chart->axisY(series)->setTitleText("成绩（分）");//设置Y轴标题
    chart->axisY(series)->setTitleBrush(QBrush(QColor(10,10,10)));
    chart->axisY(series)->setTitleFont(QFont("微软雅黑"));
    chart->axisY(series)->setTitleVisible(true);
    //Y轴网格
    chart->axisY(series)->setGridLineColor(QColor(10,10,10));//设置Y轴网格线颜色
    chart->axisY(series)->setGridLineVisible(true);
    //Y轴标签
    chart->axisY(series)->setLabelsAngle(30);
    chart->axisY(series)->setLabelsColor(QColor(10,10,10));
    chart->axisY(series)->setLabelsFont(QFont("Arial"));
    chart->axisY(series)->setLabelsVisible(true);
    //Y轴轴线
    chart->axisY(series)->setLinePenColor(QColor(10,10,10));
    chart->axisY(series)->setLineVisible(true);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    h->setCentralWidget(chartView);
    h->resize(1920, 1080);
    h->show();
}



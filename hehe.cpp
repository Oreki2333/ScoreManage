#include "hehe.h"
#include "ui_hehe.h"

hehe::hehe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hehe)
{
    ui->setupUi(this);
    setWindowTitle("近三年统计图");
}

hehe::~hehe()
{
    delete ui;
}

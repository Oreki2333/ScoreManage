#ifndef HEHE_H
#define HEHE_H

#include <QMainWindow>

namespace Ui {
class hehe;
}

class hehe : public QMainWindow
{
    Q_OBJECT

public:
    explicit hehe(QWidget *parent = nullptr);
    ~hehe();

private:
    Ui::hehe *ui;
};

#endif // HEHE_H

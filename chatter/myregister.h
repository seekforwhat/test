#ifndef MYREGISTER_H
#define MYREGISTER_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QPainter>
#include <QPaintEvent>


namespace Ui {
class myregister;
}

class myregister : public QDialog
{
    Q_OBJECT

public:
    explicit myregister(QWidget *parent = nullptr);
    ~myregister();
    bool IsEnglish(QString &qstrSrc);
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_nakButton_clicked();
    void on_ackButton_clicked();

private:
    Ui::myregister *ui;
};

#endif // MYREGISTER_H

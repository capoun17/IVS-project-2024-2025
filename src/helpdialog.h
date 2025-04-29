#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

class QTableWidget;

class helpdialog : public QDialog
{
    Q_OBJECT

public:
    helpdialog(QWidget *parent = nullptr);
    ~helpdialog();

private:
    QTableWidget *table;
};

#endif // HELPDIALOG_H

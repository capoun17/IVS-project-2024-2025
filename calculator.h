#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QKeyEvent>
#include "mathlib.h"
#include "helpdialog.h"

class QPushButton;
class helpdialog;


class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void digitPressed();
    void operationPressed();
    void equalPressed();
    void clearEntry();
    void clearAll();
    void deleteLastChar();
    void changeSign();
    void decimalPointPressed();
    void factorialPressed();
    void powerPressed();
    void rootPressed();
    void gcdPressed();
    void openHelpDialog();

private:
    // UI Elements
    QWidget *centralWidget;
    QGridLayout *mainLayout;
    QLabel *operationDisplay;
    QLabel *resultDisplay;
    QFrame *horizontalLine;

    // Calculator state
    QString currentInput;
    QString firstOperand;
    QString secondOperand;
    QString currentOperation;
    bool isNewInput;
    bool hasError;
    bool justPressedEqual;

    // Helper methods
    void setupUi();
    void connectSignals();
    void createButton(const QString &text, int row, int col,
                      const QString &styleSheet = "", int rowSpan = 1, int colSpan = 1);
    void updateDisplay();
    void processOperation();
    QString calculateResult();
    void handleError(const std::exception &e);
    void setActiveOperand(const QString &operand);
    QString getActiveOperand();
    void setActiveOperand(double value);

    helpdialog *hdialog;
    QPushButton *helpButton;

};

#endif // CALCULATOR_H

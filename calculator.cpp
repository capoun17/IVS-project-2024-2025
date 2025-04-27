#include "calculator.h"
#include <QVBoxLayout>
#include <QFont>
#include <QDebug>
#include <cmath>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), isNewInput(true), hasError(false), justPressedEqual(false)
{
    setWindowTitle("skibidi kalkulačka");
    setMinimumSize(300, 500);

    setupUi();
    connectSignals();

    // Initialize calculator state
    clearAll();
}

Calculator::~Calculator()
{
}

void Calculator::setupUi()
{
    // Create central widget and main layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create display area
    QVBoxLayout *displayLayout = new QVBoxLayout();
    displayLayout->setContentsMargins(10, 10, 10, 0);

    operationDisplay = new QLabel("");
    QFont operationFont("Arial", 14);
    operationDisplay->setFont(operationFont);
    operationDisplay->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    operationDisplay->setMinimumHeight(30);

    resultDisplay = new QLabel("0");
    QFont resultFont("Arial", 36, QFont::Bold);
    resultDisplay->setFont(resultFont);
    resultDisplay->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    resultDisplay->setMinimumHeight(60);

    horizontalLine = new QFrame();
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);

    displayLayout->addWidget(operationDisplay);
    displayLayout->addWidget(horizontalLine);
    displayLayout->addWidget(resultDisplay);

    QWidget *displayWidget = new QWidget();
    displayWidget->setLayout(displayLayout);
    displayWidget->setStyleSheet("background-color: #D3D3D3;");

    mainLayout->addWidget(displayWidget, 0, 0, 1, 5);

    // Create buttons
    QString darkButtonStyle = "QPushButton { background-color: #333333; color: white; border: none; font-size: 16px; } "
                              "QPushButton:hover { background-color: #7E7E7E; }";

    QString lightButtonStyle = "QPushButton { background-color: #C0C0C0; color: black; border: none; font-size: 16px; } "
                               "QPushButton:hover { background-color: #7E7E7E; }";

    QString orangeButtonStyle = "QPushButton { background-color: #FFA500; color: white; border: none; font-size: 16px; } "
                                "QPushButton:hover { background-color: #7E7E7E; }";

    // First row
    createButton("CE", 1, 0, darkButtonStyle);
    createButton("C", 1, 1, darkButtonStyle);
    createButton("DEL", 1, 2, darkButtonStyle);
    createButton("/", 1, 3, darkButtonStyle);
    createButton("y√x", 1, 4, darkButtonStyle);

    // Second row
    createButton("7", 2, 0, lightButtonStyle);
    createButton("8", 2, 1, lightButtonStyle);
    createButton("9", 2, 2, lightButtonStyle);
    createButton("x", 2, 3, darkButtonStyle);
    createButton("^", 2, 4, darkButtonStyle);

    // Third row
    createButton("4", 3, 0, lightButtonStyle);
    createButton("5", 3, 1, lightButtonStyle);
    createButton("6", 3, 2, lightButtonStyle);
    createButton("-", 3, 3, darkButtonStyle);
    createButton("x|y\nmax", 3, 4, darkButtonStyle);

    // Fourth row
    createButton("1", 4, 0, lightButtonStyle);
    createButton("2", 4, 1, lightButtonStyle);
    createButton("3", 4, 2, lightButtonStyle);
    createButton("+", 4, 3, darkButtonStyle);
    createButton("x!", 4, 4, darkButtonStyle);

    // Fifth row
    createButton("+/-", 5, 0, lightButtonStyle);
    createButton("0", 5, 1, lightButtonStyle);
    createButton(",", 5, 2, lightButtonStyle);
    createButton("=", 5, 3, orangeButtonStyle, 1, 2);
}

void Calculator::createButton(const QString &text, int row, int col,
                              const QString &styleSheet, int rowSpan, int colSpan)
{
    QPushButton *button = new QPushButton(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setStyleSheet(styleSheet);

    mainLayout->addWidget(button, row, col, rowSpan, colSpan);

    // Connect signals based on button type
    if (text >= "0" && text <= "9") {
        connect(button, &QPushButton::clicked, this, &Calculator::digitPressed);
    } else if (text == "+" || text == "-" || text == "x" || text == "/") {
        connect(button, &QPushButton::clicked, this, &Calculator::operationPressed);
    } else if (text == "=") {
        connect(button, &QPushButton::clicked, this, &Calculator::equalPressed);
    } else if (text == "CE") {
        connect(button, &QPushButton::clicked, this, &Calculator::clearEntry);
    } else if (text == "C") {
        connect(button, &QPushButton::clicked, this, &Calculator::clearAll);
    } else if (text == "DEL") {
        connect(button, &QPushButton::clicked, this, &Calculator::deleteLastChar);
    } else if (text == "+/-") {
        connect(button, &QPushButton::clicked, this, &Calculator::changeSign);
    } else if (text == ",") {
        connect(button, &QPushButton::clicked, this, &Calculator::decimalPointPressed);
    } else if (text == "x!") {
        connect(button, &QPushButton::clicked, this, &Calculator::factorialPressed);
    } else if (text == "^") {
        connect(button, &QPushButton::clicked, this, &Calculator::powerPressed);
    } else if (text == "y√x") {
        connect(button, &QPushButton::clicked, this, &Calculator::rootPressed);
    } else if (text == "x|y\nmax") {
        connect(button, &QPushButton::clicked, this, &Calculator::gcdPressed);
    }
}

void Calculator::connectSignals()
{
    // All signals are connected in createButton method
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        currentInput += QString::number(event->key() - Qt::Key_0);
        updateDisplay();
        break;
    case Qt::Key_Plus:
        currentOperation = "+";
        processOperation();
        break;
    case Qt::Key_Minus:
        currentOperation = "-";
        processOperation();
        break;
    case Qt::Key_Asterisk:
        currentOperation = "x";
        processOperation();
        break;
    case Qt::Key_Slash:
        currentOperation = "/";
        processOperation();
        break;
    case Qt::Key_Period:
    case Qt::Key_Comma:
        decimalPointPressed();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        equalPressed();
        break;
    case Qt::Key_Backspace:
        deleteLastChar();
        break;
    case Qt::Key_Escape:
        clearAll();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void Calculator::digitPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if (justPressedEqual) {
        // If we just pressed equal and now pressing a digit, clear everything
        clearAll();
        justPressedEqual = false;
    }

    if (isNewInput) {
        currentInput = "";
        isNewInput = false;
    }

    if (hasError) {
        clearAll();
        hasError = false;
    }

    currentInput += button->text();
    updateDisplay();
}

void Calculator::operationPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString newOperation = button->text();

    if (justPressedEqual) {
        // If we just pressed equal and then an operation, use the result as first operand
        currentOperation = newOperation;
        justPressedEqual = false;
        updateDisplay();
        return;
    }

    currentOperation = newOperation;
    processOperation();
}

void Calculator::processOperation()
{
    if (hasError) {
        clearAll();
        return;
    }

    // If we already have first operand and operation, calculate result first
    if (!firstOperand.isEmpty() && !currentOperation.isEmpty() && !currentInput.isEmpty()) {
        secondOperand = currentInput;
        QString result = calculateResult();

        if (!hasError) {
            firstOperand = result;
            secondOperand = "";
            currentInput = "";
        }
    } else if (currentInput.isEmpty() && firstOperand.isEmpty()) {
        // If no input and no first operand, use 0 as first operand
        firstOperand = "0";
    } else if (!currentInput.isEmpty()) {
        // Normal case: set first operand and clear current input
        firstOperand = currentInput;
        currentInput = "";
    }

    isNewInput = true;
    updateDisplay();
}

void Calculator::equalPressed()
{
    if (hasError) {
        clearAll();
        return;
    }

    if (firstOperand.isEmpty() || currentOperation.isEmpty()) {
        // If no operation is set, just keep the current input
        if (!currentInput.isEmpty()) {
            firstOperand = currentInput;
        }
        updateDisplay();
        return;
    }

    if (!currentInput.isEmpty()) {
        secondOperand = currentInput;
    } else if (secondOperand.isEmpty()) {
        // If no second operand, use the first operand
        secondOperand = firstOperand;
    }

    // Store the full expression for history
    QString fullExpression = firstOperand + " " + currentOperation + " " + secondOperand + " =";

    QString result = calculateResult();

    if (!hasError) {
        // Store the full expression in history
        operationDisplay->setText(fullExpression);

        firstOperand = result;
        currentInput = result;
        currentOperation = "";
        secondOperand = "";
    }

    isNewInput = true;
    justPressedEqual = true;  // Set flag that we just pressed equal
    resultDisplay->setText(result);
}

void Calculator::clearEntry()
{
    currentInput = "0";
    isNewInput = true;
    updateDisplay();
}

void Calculator::clearAll()
{
    currentInput = "";
    firstOperand = "";
    secondOperand = "";
    currentOperation = "";
    isNewInput = true;
    hasError = false;
    justPressedEqual = false;
    updateDisplay();
}

void Calculator::deleteLastChar()
{
    if (!currentInput.isEmpty()) {
        currentInput.chop(1);

        // If we deleted all characters, set to "0" instead of showing first operand
        if (currentInput.isEmpty()) {
            currentInput = "0";
            isNewInput = true;
        }

        updateDisplay();
    }
}

void Calculator::changeSign()
{
    if (currentInput.isEmpty()) {
        return;
    }

    if (currentInput.startsWith('-')) {
        currentInput.remove(0, 1);
    } else {
        currentInput.prepend('-');
    }

    updateDisplay();
}

void Calculator::decimalPointPressed()
{
    if (isNewInput) {
        currentInput = "0";
        isNewInput = false;
    }

    if (!currentInput.contains(',')) {
        currentInput += ',';
    }

    updateDisplay();
}

void Calculator::factorialPressed()
{
    if (currentInput.isEmpty() && firstOperand.isEmpty()) {
        return;
    }

    QString operand = getActiveOperand();

    // Factorial only works on integers
    bool ok;
    int value = operand.toInt(&ok);

    if (!ok) {
        handleError(std::invalid_argument("Factorial requires an integer"));
        return;
    }

    try {
        int result = factorial(value);
        setActiveOperand(result);
        updateDisplay();
    } catch (const std::exception &e) {
        handleError(e);
    }

    isNewInput = true;
    justPressedEqual = true;  // Treat factorial like other evaluated operations
}

void Calculator::powerPressed()
{
    currentOperation = "^";
    processOperation();
}

void Calculator::rootPressed()
{
    currentOperation = "√";
    processOperation();
}

void Calculator::gcdPressed()
{
    currentOperation = "x|y";
    processOperation();
}

void Calculator::updateDisplay()
{
    // Don't update history if we just pressed equal (it's handled in equalPressed)
    if (!justPressedEqual) {
        // Update operation display (history)
        QString operationText = "";

        if (!firstOperand.isEmpty()) {
            operationText = firstOperand;

            if (!currentOperation.isEmpty()) {
                operationText += " " + currentOperation;
            }
        }

        operationDisplay->setText(operationText);
    }

    // Update result display
    if (hasError) {
        resultDisplay->setText("Error");
    } else if (!currentInput.isEmpty()) {
        resultDisplay->setText(currentInput);
    } else if (!firstOperand.isEmpty()) {
        resultDisplay->setText(firstOperand);
    } else {
        resultDisplay->setText("0");
    }
}

QString Calculator::calculateResult()
{
    if (firstOperand.isEmpty() || secondOperand.isEmpty()) {
        return currentInput;
    }

    // Convert operands to numbers, handling decimal point
    bool ok1, ok2;
    double num1 = firstOperand.replace(',', '.').toDouble(&ok1);
    double num2 = secondOperand.replace(',', '.').toDouble(&ok2);

    if (!ok1 || !ok2) {
        handleError(std::invalid_argument("Invalid number format"));
        return "0";
    }

    try {
        double result = 0;

        // For integer-only operations, check if values are integers
        bool isInt1 = (num1 == std::floor(num1));
        bool isInt2 = (num2 == std::floor(num2));

        if (currentOperation == "+") {
            if (isInt1 && isInt2 && num1 <= INT_MAX && num1 >= INT_MIN &&
                num2 <= INT_MAX && num2 >= INT_MIN) {
                result = add(static_cast<int>(num1), static_cast<int>(num2));
            } else {
                result = num1 + num2;
            }
        } else if (currentOperation == "-") {
            if (isInt1 && isInt2 && num1 <= INT_MAX && num1 >= INT_MIN &&
                num2 <= INT_MAX && num2 >= INT_MIN) {
                result = substract(static_cast<int>(num1), static_cast<int>(num2));
            } else {
                result = num1 - num2;
            }
        } else if (currentOperation == "x") {
            if (isInt1 && isInt2 && num1 <= INT_MAX && num1 >= INT_MIN &&
                num2 <= INT_MAX && num2 >= INT_MIN) {
                result = multiply(static_cast<int>(num1), static_cast<int>(num2));
            } else {
                result = num1 * num2;
            }
        } else if (currentOperation == "/") {
            if (num2 == 0) {
                throw std::invalid_argument("Division by zero");
            }

            if (isInt1 && isInt2 && num1 <= INT_MAX && num1 >= INT_MIN &&
                num2 <= INT_MAX && num2 >= INT_MIN) {
                result = divide(static_cast<int>(num1), static_cast<int>(num2));
            } else {
                result = num1 / num2;
            }
        } else if (currentOperation == "^") {
            if (isInt1 && isInt2 && num2 >= 0 && num2 <= INT_MAX) {
                result = power(static_cast<int>(num1), static_cast<int>(num2));
            } else {
                result = std::pow(num1, num2);
            }
        } else if (currentOperation == "x|y") {
            if (!isInt1 || !isInt2) {
                throw std::invalid_argument("GCD requires integers");
            }
            result = greatest_common_divisor(static_cast<int>(num1), static_cast<int>(num2));
        } else if (currentOperation == "√") {
            if (!isInt1 || !isInt2) {
                throw std::invalid_argument("Root operation requires integers");
            }
            result = root(static_cast<int>(num2), static_cast<int>(num1));
        }

        // Format the result
        QString resultStr = QString::number(result, 'g', 15);
        resultStr.replace('.', ',');  // Use comma as decimal separator

        // Remove trailing zeros after decimal point
        if (resultStr.contains(',')) {
            while (resultStr.endsWith('0')) {
                resultStr.chop(1);
            }
            if (resultStr.endsWith(',')) {
                resultStr.chop(1);
            }
        }

        return resultStr;

    } catch (const std::exception &e) {
        handleError(e);
        return "0";
    }
}

void Calculator::handleError(const std::exception &e)
{
    hasError = true;
    resultDisplay->setText(QString("Error: %1").arg(e.what()));
    currentInput = "";
}

QString Calculator::getActiveOperand()
{
    if (!currentInput.isEmpty()) {
        return currentInput;
    } else if (!firstOperand.isEmpty()) {
        return firstOperand;
    }
    return "0";
}

void Calculator::setActiveOperand(const QString &operand)
{
    if (currentInput.isEmpty()) {
        firstOperand = operand;
    } else {
        currentInput = operand;
    }
}

void Calculator::setActiveOperand(double value)
{
    QString valueStr = QString::number(value, 'g', 15);
    valueStr.replace('.', ',');  // Use comma as decimal separator

    // Remove trailing zeros after decimal point
    if (valueStr.contains(',')) {
        while (valueStr.endsWith('0')) {
            valueStr.chop(1);
        }
        if (valueStr.endsWith(',')) {
            valueStr.chop(1);
        }
    }

    setActiveOperand(valueStr);
}

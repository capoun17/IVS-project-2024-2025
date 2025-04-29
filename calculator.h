#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QKeyEvent>
#include <QFont>
#include "mathlib.h"
#include "helpdialog.h"

class QPushButton;
class helpdialog;

/**
 * @brief The Calculator class implements a graphical calculator application
 *
 * This class provides a user interface for performing mathematical operations
 * including basic arithmetic, power, root, factorial, and GCD calculations.
 * It uses the mathlib library for the actual mathematical operations.
 */
class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Calculator class
     * @param parent The parent widget
     */
    Calculator(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Calculator class
     */
    ~Calculator();

protected:
    /**
     * @brief Handles keyboard key press events
     * @param event The key event to process
     */
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    /**
     * @brief Handles digit button presses
     */
    void digitPressed();

    /**
     * @brief Handles operation button presses
     */
    void operationPressed();

    /**
     * @brief Handles equal button press
     */
    void equalPressed();

    /**
     * @brief Clears the current entry
     */
    void clearEntry();

    /**
     * @brief Clears all inputs and operations
     */
    void clearAll();

    /**
     * @brief Deletes the last character of the current input
     */
    void deleteLastChar();

    /**
     * @brief Changes the sign of the current input
     */
    void changeSign();

    /**
     * @brief Adds a decimal point to the current input
     */
    void decimalPointPressed();

    /**
     * @brief Calculates the factorial of the current input
     */
    void factorialPressed();

    /**
     * @brief Sets up the power operation
     */
    void powerPressed();

    /**
     * @brief Sets up the root operation
     */
    void rootPressed();

    /**
     * @brief Sets up the greatest common divisor operation
     */
    void gcdPressed();

    /**
     * @brief Opens the help dialog
     */
    void openHelpDialog();

private:
    // UI Elements
    /**
     * @brief The central widget of the main window
     */
    QWidget *centralWidget;

    /**
     * @brief The main layout for the calculator
     */
    QGridLayout *mainLayout;

    /**
     * @brief Label for displaying the current operation
     */
    QLabel *operationDisplay;

    /**
     * @brief Label for displaying the result
     */
    QLabel *resultDisplay;

    /**
     * @brief Horizontal line separating the displays
     */
    QFrame *horizontalLine;

    /**
     * @brief Normal font for result display
     */
    QFont normalFont;

    /**
     * @brief Smaller font for error messages
     */
    QFont errorFont;

    // Calculator state
    /**
     * @brief The current input string
     */
    QString currentInput;

    /**
     * @brief The first operand for binary operations
     */
    QString firstOperand;

    /**
     * @brief The second operand for binary operations
     */
    QString secondOperand;

    /**
     * @brief The current operation symbol
     */
    QString currentOperation;

    /**
     * @brief Flag indicating if the next digit press should start a new input
     */
    bool isNewInput;

    /**
     * @brief Flag indicating if an error has occurred
     */
    bool hasError;

    /**
     * @brief Flag indicating if the equal button was just pressed
     */
    bool justPressedEqual;

    // Helper methods
    /**
     * @brief Sets up the user interface
     */
    void setupUi();

    /**
     * @brief Connects signals and slots
     */
    void connectSignals();

    /**
     * @brief Creates a button with the specified properties
     * @param text The text to display on the button
     * @param row The row position in the grid
     * @param col The column position in the grid
     * @param styleSheet The CSS style sheet for the button
     * @param rowSpan The number of rows the button spans
     * @param colSpan The number of columns the button spans
     */
    void createButton(const QString &text, int row, int col,
                      const QString &styleSheet = "", int rowSpan = 1, int colSpan = 1);

    /**
     * @brief Updates the display with the current state
     */
    void updateDisplay();

    /**
     * @brief Processes the current operation
     */
    void processOperation();

    /**
     * @brief Calculates the result of the current operation
     * @return The result as a string
     */
    QString calculateResult();

    /**
     * @brief Handles errors from mathematical operations
     * @param e The exception that occurred
     */
    void handleError(const std::exception &e);

    /**
     * @brief Sets the active operand to the specified value
     * @param operand The operand value as a string
     */
    void setActiveOperand(const QString &operand);

    /**
     * @brief Gets the active operand
     * @return The active operand as a string
     */
    QString getActiveOperand();

    /**
     * @brief Sets the active operand to the specified value
     * @param value The operand value as a double
     */
    void setActiveOperand(double value);

    /**
     * @brief The help dialog
     */
    helpdialog *hdialog;

    /**
     * @brief Button to open the help dialog
     */
    QPushButton *helpButton;
};

#endif // CALCULATOR_H

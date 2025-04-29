#include "helpdialog.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

helpdialog::helpdialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Calculator Help Guide");
    resize(600, 440);

    // Create table for help
    table = new QTableWidget(13, 4, this);
    table->setHorizontalHeaderLabels({"Symbol", "Function", "Example/Description", "Keyboard Shortcut"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setStyleSheet(
        "QTableWidget { background-color: #D3D3D3; gridline-color: #7E7E7E; font-size: 14px; color: black; } "
        "QHeaderView::section { background-color: #333333; color: white; padding: 5px; font-size: 14px; } "
        "QTableWidget::item:selected { background-color: #FFA500; color: black; } "
        );


    QStringList symbols = { "+", "-", "x", "/", "^", "y√x", "x!", "x|y", "+/-", "C", "CE", "DEL", "=" };
    QStringList meanings = {
        "Addition",
        "Subtraction",
        "Multiplication",
        "Division",
        "Power",
        "Root",
        "Factorial",
        "Greatest Common Divisor",
        "Change Sign",
        "Clear",
        "Clear Entry",
        "Delete",
        "Calculate"
    };
    QStringList shortcuts = {
        "+",
        "-",
        "*",
        "/",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "Backspace",
        "Enter"
    };

    QStringList examples = {
        "2 + 3 = 5",
        "5 - 3 = 2",
        "5 x 3 = 15",
        "15 / 3 = 5",
        "2 ^ 5 = 32",
        "3 √ 27 = 3",
        "5 ! = 120",
        "18 | 12 = 6",
        "(-5) >> 5",
        "remove all",
        "remove entry",
        "remove last digit",
        "calculate result"
    };

    for (int i = 0; i < symbols.size(); ++i)
    {
        QTableWidgetItem *symbolItem = new QTableWidgetItem(symbols[i]);
        symbolItem->setTextAlignment(Qt::AlignCenter); // << center the symbol

        table->setItem(i, 0, symbolItem);
        table->setItem(i, 1, new QTableWidgetItem(meanings[i]));
        table->setItem(i, 2, new QTableWidgetItem(examples[i]));
        table->setItem(i, 3, new QTableWidgetItem(shortcuts[i]));
    }

    table->resizeColumnsToContents();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);
    setLayout(layout);
}

helpdialog::~helpdialog()
{
}

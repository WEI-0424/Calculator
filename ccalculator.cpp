#include "ccalculator.h"
#include <QDebug>

CCalculator::CCalculator(QWidget *parent)
    : QWidget(parent), storedValue(0.0)
{
    display = new QLineEdit(this);
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setMinimumHeight(50);
    display->setStyleSheet("font-size: 24px; padding: 6px;");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(display, 0, 0, 1, 4);

    QStringList buttonLabels = {
        "←", "/", "*", "-",
        "7", "8", "9", "+",
        "4", "5", "6", "=",
        "1", "2", "3", "C",
        "0", "."
    };

    QList<QPushButton*> buttons;
    for (const QString &text : buttonLabels) {
        QPushButton *btn = new QPushButton(text);
        btn->setMinimumSize(60, 60);
        btn->setStyleSheet("font-size: 22px; font-weight: bold;");
        connect(btn, &QPushButton::clicked, this, &CCalculator::onButtonClicked);
        buttons.append(btn);
    }

    // 手動安排接近圖片的排列
    layout->addWidget(buttons[0], 1, 0);  // ←
    layout->addWidget(buttons[1], 1, 1);  // /
    layout->addWidget(buttons[2], 1, 2);  // *
    layout->addWidget(buttons[3], 1, 3);  // -

    layout->addWidget(buttons[4], 2, 0);  // 7
    layout->addWidget(buttons[5], 2, 1);  // 8
    layout->addWidget(buttons[6], 2, 2);  // 9
    layout->addWidget(buttons[7], 2, 3, 2, 1);  // +（拉長兩格）

    layout->addWidget(buttons[8], 3, 0);  // 4
    layout->addWidget(buttons[9], 3, 1);  // 5
    layout->addWidget(buttons[10], 3, 2); // 6

    layout->addWidget(buttons[11], 4, 3, 2, 1);  // =（拉長兩格）
    layout->addWidget(buttons[12], 4, 0);  // 1
    layout->addWidget(buttons[13], 4, 1);  // 2
    layout->addWidget(buttons[14], 4, 2);  // 3

    layout->addWidget(buttons[15], 1, 4);  // C
    layout->addWidget(buttons[16], 5, 0, 1, 2);  // 0
    layout->addWidget(buttons[17], 5, 2);  // .

    setLayout(layout);
    setWindowTitle("C Calculator");
    resize(350, 500);
}

void CCalculator::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString text = button->text();

    if (text == "C") {
        display->clear();
        currentInput.clear();
        storedValue = 0.0;
        pendingOperator.clear();
        return;
    }

    if (text == "←") {
        currentInput.chop(1);
        display->setText(currentInput);
        return;
    }

    if (text == "=") {
        if (!pendingOperator.isEmpty()) {
            double operand = currentInput.toDouble();
            calculate(operand, pendingOperator);
            pendingOperator.clear();
            currentInput = QString::number(storedValue);
            display->setText(currentInput);
        }
        return;
    }

    if (text == "+" || text == "-" || text == "*" || text == "/") {
        if (!currentInput.isEmpty()) {
            double operand = currentInput.toDouble();
            if (pendingOperator.isEmpty())
                storedValue = operand;
            else
                calculate(operand, pendingOperator);
            pendingOperator = text;
            currentInput.clear();
        }
        return;
    }

    currentInput += text;
    display->setText(currentInput);
}

void CCalculator::calculate(double operand, const QString &operatorSymbol)
{
    if (operatorSymbol == "+")
        storedValue += operand;
    else if (operatorSymbol == "-")
        storedValue -= operand;
    else if (operatorSymbol == "*")
        storedValue *= operand;
    else if (operatorSymbol == "/")
        if (operand != 0)
            storedValue /= operand;
}

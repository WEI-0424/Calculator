#ifndef CCALCULATOR_H
#define CCALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class CCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit CCalculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    QString currentInput;
    QString pendingOperator;
    double storedValue;

    void calculate(double operand, const QString &operatorSymbol);
};

#endif // CCALCULATOR_H

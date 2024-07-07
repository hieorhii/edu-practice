#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    // Конструктор
    Calculator();

    // Функции для выполнения операций
    double sum(double a, double b);
    double dif(double a, double b);
    double mul(double a, double b);
    double div(double a, double b);

    // Деструктор
    ~Calculator();
};

#endif // CALCULATOR_H

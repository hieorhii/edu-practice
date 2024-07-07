#include <calculator.h>
#include <iostream>

using namespace std;

int main()
{
    double a = 10.0, b = 5.0;
    cout << a << " " << b << endl;

    Calculator calc;
    cout << "sum " << calc.sum(a, b) << endl;
    cout << "dif " << calc.dif(a, b) << endl;
    cout << "mul " << calc.mul(a, b) << endl;
    cout << "div " << calc.div(a, b) << endl;

    return 0;
}

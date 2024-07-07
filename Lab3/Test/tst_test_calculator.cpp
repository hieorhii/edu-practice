#include <QtTest>

#include "../Calc/calculator.h"

class test_calculator : public QObject
{
    Q_OBJECT

public:
    test_calculator();
    ~test_calculator();

private slots:
    void testSum();
};

test_calculator::test_calculator() {}

test_calculator::~test_calculator() {}

void test_calculator::testSum() {
    Calculator calc;
    QCOMPARE(calc.sum(2.0, 3.0), 5.0);
    QCOMPARE(calc.sum(8.0, 3.0), 11.0);
    QCOMPARE(calc.sum(-8.0, 3.0), -5.0);
}

QTEST_APPLESS_MAIN(test_calculator)

#include "tst_test_calculator.moc"

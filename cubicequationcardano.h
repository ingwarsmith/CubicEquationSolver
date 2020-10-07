#ifndef CUBICEQUATIONCARDANO_H
#define CUBICEQUATIONCARDANO_H

#include <QVector>



class CubicEquationCardano
{
    // Класс, реализующий решение кубического уравнения методом Кардано (вычисляются только действительные корни).
    // Уравнение общего вида ax^3 + bx^2 + cx + d = 0 реализовано так:
    //   koeff_A*x^3 + koeff_B*x^2 + koeff_C*x + koeff_D = 0.  (1)
    // При этом по умолчанию koeff_A = 1, т.е. решается уравнение вида
    //   x^3 + koeff_B*x^2 + koeff_C*x + koeff_D = 0.           (2)
    // В алгоритме класса вид (1) приводится к канонической форме
    //   y^3 + koeff_p*y + koeff_q = 0                        (3)
    // с помощью замены переменных:
    //   y = x + koeff_B / (3.0*koeff_A)     => x = y - koeff_B / (3.0*koeff_A)
    //   p = (3.0*koeff_A*koeff_C - koeff_B^2) / (3.0*koeff_A^2)
    //   q = (2.0*koeff_B^3 - 9.0*koeff_A*koeff_B*koeff_C + 27.0*koeff_A^2*koeff_D) / (27.0*koeff_A^3)

public:
    CubicEquationCardano(double koeff_B, double koeff_C, double koeff_D, double koeff_A = 1.0);
    bool            isRootsAreValid();
    QVector<double> returnRealRoots();
    void            printRealRootsInStdOut();

private:
    QVector<double> roots;
    double          alpha;
    double          beta;
    double          Q;
    double          p;
    double          q;
    double          b_, c_, d_, a_;
};

#endif // CUBICEQUATIONCARDANO_H

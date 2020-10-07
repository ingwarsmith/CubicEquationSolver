#include "cubicequationcardano.h"

#include <cmath>
#include <iostream>
#include <complex>

CubicEquationCardano::CubicEquationCardano(double koeff_B, double koeff_C, double koeff_D, double koeff_A)
{
    a_ = koeff_A;
    b_ = koeff_B;
    c_ = koeff_C;
    d_ = koeff_D;

    p = (3.0*a_*c_ - std::pow(b_, 2.0)) / (3.0*std::pow(a_, 2.0));
    q = (2.0*std::pow(b_, 3.0) - 9.0*a_*b_*c_ + 27.0*std::pow(a_, 2.0)*d_) / (27.0*std::pow(a_, 3.0));
    Q = std::pow((p/3.0), 3.0) + std::pow((q/2.0), 2.0);

    if (Q > 0.0)
    {
        double base1 = -q/2.0 + std::sqrt(Q);
        double signBase1 = 0.0;
        if (base1 > 0)
            signBase1 = 1.0;
        else
            signBase1 = -1.0;
        alpha = signBase1 * std::pow(std::fabs(base1), (1.0/3.0));

        double base2 = -q/2.0 - std::sqrt(Q);
        double signBase2 = 0.0;
        if (base2 >= 0)
            signBase2 = 1.0;
        else
            signBase2 = -1.0;
        beta = signBase2 * std::pow(std::fabs(base2), (1.0/3.0));

        // нас интересует лишь один вещественный корень (другие корни комплексные):
        double y = alpha + beta;
        double x = y - b_ / (3.0*a_);
        roots.append(x);
    }
    else if (qFuzzyIsNull(Q))
    {
        double base = -q/2.0;
        double signBase = 0.0;
        if (base > 0)
            signBase = 1.0;
        else
            signBase = -1.0;
        alpha = signBase * std::pow(std::fabs(base), (1.0/3.0));

        double y1 = alpha * 2.0;

        double x1 = y1 - b_ / (3.0*a_);

        roots.append(x1);

        if (! (qFuzzyIsNull(p) && qFuzzyIsNull(q)))
        {
            double y2_3 = -alpha;

            double x2_3 = y2_3 - b_ / (3.0*a_);

            roots.append(x2_3); // ещё один двухкратный корень
        }
    }
    else /*Q < 0*/
    {
        using std::complex;

        double A_param = - q / 2.0;
        double B_param_alpha = std::sqrt(std::fabs(Q));
        double B_param_beta = - B_param_alpha;

        double phi_alpha = atan2(B_param_alpha, A_param);
        double phi_beta = atan2(B_param_beta, A_param);
        double N = std::pow((A_param*A_param + std::fabs(Q)), (1.0/6.0));

        QVector<complex<double> > alpha_values;
        QVector<complex<double> > beta_values;

        for (int n = 0; n < 3; ++n)
        {
            double nDbl = static_cast<double>(n);
            double sinusWithI = sin((phi_alpha + 2.0*M_PI*nDbl)/3.0);
            double cosinusWoI = cos((phi_alpha + 2.0*M_PI*nDbl)/3.0);
            complex<double> E_pow_iDivN_alpha(cosinusWoI, sinusWithI);
            E_pow_iDivN_alpha *= N;
            sinusWithI = sin((phi_beta + 2.0*M_PI*n)/3.0);
            cosinusWoI = cos((phi_beta + 2.0*M_PI*n)/3.0);
            complex<double> E_pow_iDivN_beta(cosinusWoI, sinusWithI);
            E_pow_iDivN_beta *= N;

            alpha_values.append(E_pow_iDivN_alpha);
            beta_values.append(E_pow_iDivN_beta);
        }

        for (int cntrAlpha = 0; cntrAlpha < alpha_values.count(); ++cntrAlpha)
        {
            for (int cntrBeta = 0; cntrBeta < beta_values.count(); ++cntrBeta)
            {
                if (cntrAlpha == cntrBeta)
                {
                    complex<double> alphaPlusBeta = alpha_values.at(cntrAlpha) + beta_values.at(cntrBeta);
                    complex<double> alphaMinusBeta = alpha_values.at(cntrAlpha) - beta_values.at(cntrBeta);
                    complex<double> y1_cmplx = alphaPlusBeta;
                    complex<double> y2_cmplx, y3_cmplx;
                    complex<double> i_ImaginaryOne(0.0, 1.0);
                    y2_cmplx = - alphaPlusBeta/2.0 + i_ImaginaryOne*std::sqrt(3.0)*alphaMinusBeta/2.0;
                    y3_cmplx = - alphaPlusBeta/2.0 - i_ImaginaryOne*std::sqrt(3.0)*alphaMinusBeta/2.0;

                    if ( qFuzzyIsNull(y1_cmplx.imag()) )
                    {
                        double x1 = y1_cmplx.real() - b_ / (3.0*a_);
                        roots.append(x1);
                    }

                    if ( qFuzzyIsNull(y2_cmplx.imag()) )
                    {
                        double x2 = y2_cmplx.real() - b_ / (3.0*a_);
                        roots.append(x2);
                    }

                    if ( qFuzzyIsNull(y3_cmplx.imag()) )
                    {
                        double x3 = y3_cmplx.real() - b_ / (3.0*a_);
                        roots.append(x3);
                    }
                }
            }
        }
    }
}

bool CubicEquationCardano::isRootsAreValid()
{
    if (roots.isEmpty())
        return true;

    for (int i = 0; i < roots.size(); ++i)
    {
        double x = roots.at(i);
        double result = a_*std::pow(x, 3.0) + b_*std::pow(x,2.0) + c_*x + d_;
        bool differenceFromZero = std::fabs(result) > 1.0e-8;
        if (differenceFromZero) return false;
        if (std::fabs(x) < 1.0e-12) roots[i] = 0.0;
    }

    return true;
}

QVector<double> CubicEquationCardano::returnRealRoots()
{
    return roots;
}

void CubicEquationCardano::printRealRootsInStdOut()
{
    using namespace std;

    cout << "Root(s):" << endl;
    for (int i = 0; i < roots.size(); ++i)
    {
        cout << "x" << (i + 1) << " = " << roots.at(i) << endl;
    }
}

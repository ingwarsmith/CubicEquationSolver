#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>
#include "cubicequationcardano.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->setVisible(false);
    ui->menuBar->setVisible(false);

    equation = NULL;

    connect(ui->btnCalc, &QPushButton::clicked, this, [&]()
    {
        // расчет

        if (ui->lned_koeff_A->text().isEmpty() || qFuzzyIsNull( ui->lned_koeff_A->text().toDouble() ))
        {
            QMessageBox::information(this,
                                     trUtf8("Ошибка ввода"),
                                     trUtf8("Обязательно указание ненулевого значения коэффициента уравнения A:"
                                            " данная программа не предназначена для решения квадратных и "
                                            "линейных уравнений."));
            return;
        }

        auto successA = false,
             successB = false,
             successC = false,
             successD = false;

        auto _A = 0.0, _B = 0.0, _C = 0.0, _D = 0.0;

        if (!ui->lned_koeff_A->text().isEmpty())
        {
            _A = ui->lned_koeff_A->text().toDouble(&successA);
            if (!successA)
            {
                QMessageBox::warning(this,
                                     trUtf8("Ошибка ввода"),
                                     trUtf8("Нечисловые данные в поле ввода коэффициента A!"));
                return;
            }
        }

        if (!ui->lned_koeff_B->text().isEmpty())
        {
            _B = ui->lned_koeff_B->text().toDouble(&successB);
            if (!successB)
            {
                QMessageBox::warning(this,
                                     trUtf8("Ошибка ввода"),
                                     trUtf8("Нечисловые данные в поле ввода коэффициента B!"));
                return;
            }
        }

        if (!ui->lned_koeff_C->text().isEmpty())
        {
            _C = ui->lned_koeff_C->text().toDouble(&successC);
            if (!successC)
            {
                QMessageBox::warning(this,
                                     trUtf8("Ошибка ввода"),
                                     trUtf8("Нечисловые данные в поле ввода коэффициента C!"));
                return;
            }
        }

        if (!ui->lned_koeff_D->text().isEmpty())
        {
            _D = ui->lned_koeff_D->text().toDouble(&successD);
            if (!successD)
            {
                QMessageBox::warning(this,
                                     trUtf8("Ошибка ввода"),
                                     trUtf8("Нечисловые данные в поле ввода коэффициента D!"));
                return;
            }
        }

        equation = new CubicEquationCardano(_B, _C, _D, _A);
        QStringList rootsListStrings;

        if (!equation->isRootsAreValid())
            QMessageBox::warning(this,
                                  trUtf8("Внимание!"),
                                  trUtf8("Значимая погрешность вычисления корней"));

        auto roots = equation->returnRealRoots();
        if (roots.isEmpty())
        {
            QMessageBox::information(this, trUtf8("Результат"), trUtf8("Действительных корней нет"));
        }
        for (int rootNum = 0; rootNum < roots.size(); ++rootNum)
        {
            rootsListStrings.append(
                        QString::number(roots.at(rootNum), 'g', 10)
                        );
        }

        ui->listWidget_Result->clear();
        ui->listWidget_Result->addItems(rootsListStrings);
        delete equation;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

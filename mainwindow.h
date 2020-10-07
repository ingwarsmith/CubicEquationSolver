#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "cubicequationcardano.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnCalc_clicked();

private:
    Ui::MainWindow *ui;
    CubicEquationCardano *equation;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"
#include <QSemaphore>

#define TRAIN_CAN_MOVE 1 // indica que o trem pode se mover
#define TRAIN_CANNOT_MOVE 0 // indica que o trem não pode se mover

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);
    void startTrains();
    void checkFirstTrainCanMove(int x, int y);
    void checkSecondTrainCanMove(int x, int y);
    void checkThirdTrainCanMove(int x, int y);
    void checkFourthTrainCanMove(int x, int y);
    void checkFifthTrainCanMove(int x, int y);

private slots:
    void on_controllerTrainOne_valueChanged(int value);

    void on_controllerTrainTwo_valueChanged(int value);

    void on_controllerTrainThree_valueChanged(int value);

    void on_controllerTrainFour_valueChanged(int value);

    void on_controllerTrainFive_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

    //Cria os semáforos
    QSemaphore firstCriticalRegion;
    QSemaphore secondCriticalRegion;
    QSemaphore thirdCriticalRegion;
    QSemaphore fourthCriticalRegion;
    QSemaphore fifthCriticalRegion;
    QSemaphore sixthCriticalRegion;
    QSemaphore seventhCriticalRegion;
};

#endif // MAINWINDOW_H

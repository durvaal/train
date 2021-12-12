#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,230,30,TRAIN_CAN_MOVE);
    trem2 = new Trem(2,500,30,TRAIN_CAN_MOVE);
    trem3 = new Trem(3,100,150,TRAIN_CAN_MOVE);
    trem4 = new Trem(4,370,150,TRAIN_CAN_MOVE);
    trem5 = new Trem(5,640,150,TRAIN_CAN_MOVE);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
}

void MainWindow::checkFirstTrainCanMove(int x, int y) {
     if (ui->label_trem2->x() <= 520 && (ui->label_trem1->x() == 480 && ui->label_trem1->y() == 30) && firstCriticalRegion.available() == 0) {
         // AWAIT SECOND TRAIN
         firstCriticalRegion.release(1);
         qDebug() << "RELEASE BY FIRST TRAIN, FIRST CRITICAL REGION AVAILABLE: " << firstCriticalRegion.available();
         trem1->setCanMove(TRAIN_CANNOT_MOVE);
         trem1->wait(1);
     } else if ((ui->label_trem1->x() == 390 && ui->label_trem1->y() == 150) && (ui->label_trem3->x() > 210 && ui->label_trem3->y() == 150) && secondCriticalRegion.available() == 0) {
         // AWAIT THIRD TRAIN
         secondCriticalRegion.release(1);
         qDebug() << "RELEASE BY FIRST TRAIN, SECOND CRITICAL REGION AVAILABLE: " << secondCriticalRegion.available();
         trem1->setCanMove(TRAIN_CANNOT_MOVE);
         trem1->wait(1);
     } else if ((ui->label_trem1->x() == 500 && ui->label_trem1->y() == 130) && ((ui->label_trem4->x() >= 370 && ui->label_trem4->x() < 520) && ui->label_trem4->y() == 150) && thirdCriticalRegion.available() == 0) {
         // AWAIT FOURTH TRAIN
         thirdCriticalRegion.release(1);
         qDebug() << "RELEASE BY FIRST TRAIN, THIRD CRITICAL REGION AVAILABLE: " << thirdCriticalRegion.available();
         trem1->setCanMove(TRAIN_CANNOT_MOVE);
         trem1->wait(1);
     } else {
         if (trem1->getCanMove() == TRAIN_CANNOT_MOVE) {
             if (firstCriticalRegion.available() == 1) {
                 firstCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FIRST TRAIN, FIRST CRITICAL REGION AVAILABLE: " << firstCriticalRegion.available();
                 trem1->setX(480);
                 trem1->setY(30);
                 trem1->setCanMove(TRAIN_CAN_MOVE);
                 trem1->start();
             }
             if (secondCriticalRegion.available() == 1) {
                 secondCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FIRST TRAIN, SECOND CRITICAL REGION AVAILABLE: " << secondCriticalRegion.available();
                 trem1->setX(390);
                 trem1->setY(150);
                 trem1->setCanMove(TRAIN_CAN_MOVE);
                 trem1->start();
             }
             if (thirdCriticalRegion.available() == 1) {
                 thirdCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FIRST TRAIN, THIRD CRITICAL REGION AVAILABLE: " << thirdCriticalRegion.available();
                 trem1->setX(500);
                 trem1->setY(130);
                 trem1->setCanMove(TRAIN_CAN_MOVE);
                 trem1->start();
             }
         } else {
            ui->label_trem1->setGeometry(x,y,21,17);
         }
     }
}

void MainWindow::checkSecondTrainCanMove(int x, int y) {
     if ((ui->label_trem1->x() > 480) && ui->label_trem2->x() == 520 && firstCriticalRegion.available() == 0) {
         // AWAIT FIRST TRAIN
         firstCriticalRegion.release(1);
         qDebug() << "RELEASE BY SECOND TRAIN, FIRST CRITICAL REGION AVAILABLE: " << firstCriticalRegion.available();
         trem2->setCanMove(TRAIN_CANNOT_MOVE);
         trem2->wait(1);
     } else if ((ui->label_trem2->x() == 660 && ui->label_trem2->y() == 150) && (ui->label_trem4->x() > 480 && ui->label_trem4->y() == 150) && fourthCriticalRegion.available() == 0) {
         // AWAIT FOURTH TRAIN
         fourthCriticalRegion.release(1);
         qDebug() << "RELEASE BY SCOND TRAIN, FOURTH CRITICAL REGION AVAILABLE: " << fourthCriticalRegion.available();
         trem2->setCanMove(TRAIN_CANNOT_MOVE);
         trem2->wait(1);
     } else if ((ui->label_trem2->x() == 770 && ui->label_trem2->y() == 130) && ((ui->label_trem5->x() >= 640 && ui->label_trem5->x() < 790) && ui->label_trem5->y() == 150) && seventhCriticalRegion.available() == 0) {
         // AWAIT FOURTH TRAIN
         seventhCriticalRegion.release(1);
         qDebug() << "RELEASE BY SCOND TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
         trem2->setCanMove(TRAIN_CANNOT_MOVE);
         trem2->wait(1);
     } else {
         if (trem2->getCanMove() == TRAIN_CANNOT_MOVE) {
             if (firstCriticalRegion.available() == 1) {
                 firstCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY SECOND TRAIN, FIRST CRITICAL REGION AVAILABLE: " << firstCriticalRegion.available();
                 trem2->setX(520);
                 trem2->setY(150);
                 trem2->setCanMove(TRAIN_CAN_MOVE);
                 trem2->start();
             }
             if (fourthCriticalRegion.available() == 1) {
                 fourthCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY SECOND TRAIN, FOURTH CRITICAL REGION AVAILABLE: " << fourthCriticalRegion.available();
                 trem2->setX(660);
                 trem2->setY(150);
                 trem2->setCanMove(TRAIN_CAN_MOVE);
                 trem2->start();
             }
             if (seventhCriticalRegion.available() == 1) {
                 seventhCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY SECOND TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
                 trem2->setX(770);
                 trem2->setY(130);
                 trem2->setCanMove(TRAIN_CAN_MOVE);
                 trem2->start();
             }
         } else {
            ui->label_trem2->setGeometry(x,y,21,17);
         }
     }
}

void MainWindow::checkThirdTrainCanMove(int x, int y) {
    if ((ui->label_trem1->x() < 390 && ui->label_trem1->y() == 150) && (ui->label_trem3->x() == 210 && ui->label_trem3->y() == 150) && secondCriticalRegion.available() == 0) {
        // AWAIT FIRST TRAIN
        secondCriticalRegion.release(1);
        qDebug() << "RELEASE BY THIRD TRAIN, SECOND CRITICAL REGION AVAILABLE: " << secondCriticalRegion.available();
        trem3->setCanMove(TRAIN_CANNOT_MOVE);
        trem3->wait(1);
     } else if ((ui->label_trem3->x() == 350 && ui->label_trem3->y() == 150) && (ui->label_trem4->x() == 370 && ui->label_trem4->y() == 170) && sixthCriticalRegion.available() == 0) {
        // AWAIT FOURTH TRAIN
        sixthCriticalRegion.release(1);
        qDebug() << "RELEASE BY THIRD TRAIN, SIXTH CRITICAL REGION AVAILABLE: " << sixthCriticalRegion.available();
        trem3->setCanMove(TRAIN_CANNOT_MOVE);
        trem3->wait(1);
    } else {
         if (trem3->getCanMove() == TRAIN_CANNOT_MOVE) {
             if (secondCriticalRegion.available() == 1) {
                 secondCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY THIRD TRAIN, SECOND CRITICAL REGION AVAILABLE: " << secondCriticalRegion.available();
                 trem3->setX(210);
                 trem3->setY(150);
                 trem3->setCanMove(TRAIN_CAN_MOVE);
                 trem3->start();
             }
             if (sixthCriticalRegion.available() == 1) {
                 sixthCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY THIRD TRAIN, SIXTH CRITICAL REGION AVAILABLE: " << sixthCriticalRegion.available();
                 trem3->setX(350);
                 trem3->setY(150);
                 trem3->setCanMove(TRAIN_CAN_MOVE);
                 trem3->start();
             }
         } else {
            ui->label_trem3->setGeometry(x,y,21,17);
         }
     }
}

void MainWindow::checkFourthTrainCanMove(int x, int y) {
    if ((ui->label_trem1->x() >= 370 && ui->label_trem1->y() == 150) && (ui->label_trem4->x() == 370 && ui->label_trem4->y() == 170) && thirdCriticalRegion.available() == 0) {
        // AWAIT FIRST TRAIN
        thirdCriticalRegion.release(1);
        qDebug() << "RELEASE BY FOURTH TRAIN, THIRD CRITICAL REGION AVAILABLE: " << thirdCriticalRegion.available();
        trem4->setCanMove(TRAIN_CANNOT_MOVE);
        trem4->wait(1);
     } else if ((ui->label_trem3->x() == 370 && ui->label_trem3->y() >= 150) && (ui->label_trem4->x() == 390 && ui->label_trem4->y() == 300) && sixthCriticalRegion.available() == 0) {
        // AWAIT THIRD TRAIN
        sixthCriticalRegion.release(1);
        qDebug() << "RELEASE BY FOURTH TRAIN, SIXTH CRITICAL REGION AVAILABLE: " << sixthCriticalRegion.available();
        trem4->setCanMove(TRAIN_CANNOT_MOVE);
        trem4->wait(1);
     } else if ((ui->label_trem4->x() == 370 && ui->label_trem4->y() == 170) && (ui->label_trem2->x() < 660 && ui->label_trem2->y() == 150) && fourthCriticalRegion.available() == 0) {
        // AWAIT SECOND TRAIN
        fourthCriticalRegion.release(1);
        qDebug() << "RELEASE BY FOURTH TRAIN, FOURTH CRITICAL REGION AVAILABLE: " << fourthCriticalRegion.available();
        trem4->setCanMove(TRAIN_CANNOT_MOVE);
        trem4->wait(1);
     } else if ((ui->label_trem4->x() == 620 && ui->label_trem4->y() == 150) && (ui->label_trem5->x() < 660 && (ui->label_trem5->y() >= 150 && ui->label_trem5->y() <= 3000)) && seventhCriticalRegion.available() == 0) {
        // AWAIT FOURTH TRAIN
        seventhCriticalRegion.release(1);
        qDebug() << "RELEASE BY FOURTH TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
        trem4->setCanMove(TRAIN_CANNOT_MOVE);
        trem4->wait(1);
     } else {
         if (trem4->getCanMove() == TRAIN_CANNOT_MOVE) {
             if (thirdCriticalRegion.available() == 1) {
                 thirdCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FOURTH TRAIN, THIRD CRITICAL REGION AVAILABLE: " << thirdCriticalRegion.available();
                 trem4->setX(370);
                 trem4->setY(170);
                 trem4->setCanMove(TRAIN_CAN_MOVE);
                 trem4->start();
             }
             if (sixthCriticalRegion.available() == 1) {
                 sixthCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FOURTH TRAIN, SIXTH CRITICAL REGION AVAILABLE: " << sixthCriticalRegion.available();
                 trem4->setX(390);
                 trem4->setY(300);
                 trem4->setCanMove(TRAIN_CAN_MOVE);
                 trem4->start();
             }
             if (fourthCriticalRegion.available() == 1) {
                 fourthCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FOURTH TRAIN, FOURTH CRITICAL REGION AVAILABLE: " << fourthCriticalRegion.available();
                 trem4->setX(480);
                 trem4->setY(150);
                 trem4->setCanMove(TRAIN_CAN_MOVE);
                 trem4->start();
             }
             if (seventhCriticalRegion.available() == 1) {
                 seventhCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FOURTH TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
                 trem4->setX(620);
                 trem4->setY(150);
                 trem4->setCanMove(TRAIN_CAN_MOVE);
                 trem4->start();
             }
         } else {
            ui->label_trem4->setGeometry(x,y,21,17);
         }
     }
}

void MainWindow::checkFifthTrainCanMove(int x, int y) {
    if ((ui->label_trem2->x() >= 770 && ui->label_trem2->y() > 130) && (ui->label_trem5->x() == 640 && ui->label_trem4->y() == 170) && fifthCriticalRegion.available() == 0) {
        // AWAIT SECOND TRAIN
        fifthCriticalRegion.release(1);
        qDebug() << "RELEASE BY FIFTH TRAIN, FIFTH CRITICAL REGION AVAILABLE: " << fifthCriticalRegion.available();
        trem5->setCanMove(TRAIN_CANNOT_MOVE);
        trem5->wait(1);
     } else if ((ui->label_trem5->x() == 660 && ui->label_trem5->y() == 300) && (ui->label_trem4->x() > 620 && ui->label_trem4->y() > 150) && seventhCriticalRegion.available() == 0) {
        // AWAIT FOURTH TRAIN
        seventhCriticalRegion.release(1);
        qDebug() << "RELEASE BY FIFTH TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
        trem5->setCanMove(TRAIN_CANNOT_MOVE);
        trem5->wait(1);
    } else {
         if (trem5->getCanMove() == TRAIN_CANNOT_MOVE) {
             if (fifthCriticalRegion.available() == 1) {
                 fifthCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FIFTH TRAIN, FIFTH CRITICAL REGION AVAILABLE: " << fifthCriticalRegion.available();
                 trem5->setX(640);
                 trem5->setY(170);
                 trem5->setCanMove(TRAIN_CAN_MOVE);
                 trem5->start();
             }
             if (seventhCriticalRegion.available() == 1) {
                 seventhCriticalRegion.acquire(1);
                 qDebug() << "ACQUIRE BY FIFTH TRAIN, SEVENTH CRITICAL REGION AVAILABLE: " << seventhCriticalRegion.available();
                 trem5->setX(660);
                 trem5->setY(300);
                 trem5->setCanMove(TRAIN_CAN_MOVE);
                 trem5->start();
             }
         } else {
            ui->label_trem3->setGeometry(x,y,21,17);
         }
     }
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        this->checkFirstTrainCanMove(x, y);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        this->checkSecondTrainCanMove(x, y);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        this->checkThirdTrainCanMove(x, y);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        this->checkFourthTrainCanMove(x, y);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Inicia todos os trens
 */
void MainWindow::startTrains()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

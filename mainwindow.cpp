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
    trem2 = new Trem(2,710,150,TRAIN_CAN_MOVE);
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
     if (ui->label_trem2->x() <= 520 && (ui->label_trem1->x() == 480 && ui->label_trem1->y() == 30)) {
         trem1->setCanMove(TRAIN_CANNOT_MOVE);
         trem1->quit();
     } else {
         if (trem1->getCanMove() == TRAIN_CANNOT_MOVE) {
             this->firstCriticalRegion.lock();
             trem1->setX(480);
             trem1->setY(30);
             trem1->setCanMove(TRAIN_CAN_MOVE);
             trem1->start();
             this->firstCriticalRegion.unlock();
         } else {
            ui->label_trem1->setGeometry(x,y,21,17);
         }
     }
}

void MainWindow::checkSecondTrainCanMove(int x, int y) {
     if ((ui->label_trem1->x() > 480) && ui->label_trem2->x() == 520) {
         this->firstCriticalRegion.lock();
         trem2->setCanMove(TRAIN_CANNOT_MOVE);
         trem2->quit();
         this->firstCriticalRegion.unlock();
     } else {
         if (trem2->getCanMove() == TRAIN_CANNOT_MOVE) {
             this->firstCriticalRegion.lock();
             trem2->setX(520);
             trem2->setY(150);
             trem2->setCanMove(TRAIN_CAN_MOVE);
             trem2->start();
             this->firstCriticalRegion.unlock();
         } else {
            ui->label_trem2->setGeometry(x,y,21,17);
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
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
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

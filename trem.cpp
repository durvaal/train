#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y, int canMove, int velocidade){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->canMove = canMove;
    this->velocidade = velocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <500)
                x+=10;
            else if (x == 500 && y < 150)
                y+=10;
            else if (x > 230 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <770)
                x+=10;
            else if (x == 770 && y < 150)
                y+=10;
            else if (x > 500 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 150 && x <370)
                x+=10;
            else if (x == 370 && y < 300)
                y+=10;
            else if (x > 100 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <640)
                x+=10;
            else if (x == 640 && y < 300)
                y+=10;
            else if (x > 370 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <910)
                x+=10;
            else if (x == 910 && y < 300)
                y+=10;
            else if (x > 640 && y == 300)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }

        msleep(velocidade);
    }
}





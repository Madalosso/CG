#include "parede.h"
#include "time.h"
#include "cstdlib"
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

parede::parede(float tam,float largura_in)
{
    //pos_x = 30;
    pos_x=30;
    srand(time(NULL));
    int r_random = rand()%20;
    largura=largura_in;
    /*if(r_random + tam > 30){
        gap_up = r_random+tam;
        gap_down = r_random;
    }else{
        if(r_random-tam<0){
            gap_up=r_random;
            gap_down = gap_up-tam;
        }
    }*/

    if(r_random >=10){
        gap_up=r_random;
        gap_down=r_random - 5;
    }else{
        gap_down=r_random;
        gap_up=r_random + 5;
    }

    //teste
    //gap_up=10;
    //gap_down=6;
    //ctor
}

void parede::draw(){
    //segmento de cima
    //printf("\n Quad sup:\n ");

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
      glVertex2f(pos_x,20);
      glVertex2f(pos_x+largura,20);
      glVertex2f(pos_x+largura,gap_up);
      glVertex2f(pos_x,gap_up);
    glEnd();

    //segmento de baixo
   glBegin(GL_POLYGON);
      glVertex2f(pos_x,gap_down);
      glVertex2f(pos_x+largura,gap_down);
      glVertex2f(pos_x+largura,0);
      glVertex2f(pos_x,0);
    glEnd();


}

parede::~parede()
{
    //dtor
}

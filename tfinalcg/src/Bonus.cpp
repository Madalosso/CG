#include "Bonus.h"
#include "time.h"
#include "cstdlib"
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

Bonus::Bonus()
{
    pos_x=30;
    srand(time(NULL));
    int r_random = rand()%18+1;

    pos_y=r_random;
    tam = 0.75;

    bonus = rand()%3+1;
}

void Bonus::draw()
{
    switch(bonus)
    {
    case 1:
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 2:
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 3:
        glColor3f(1.0f, 0.0f, 1.0f);
        break;
    }
    glBegin(GL_POLYGON);
    glVertex2f(pos_x,pos_y);
    glVertex2f(pos_x+tam,pos_y);
    glVertex2f(pos_x+tam,pos_y-tam);
    glVertex2f(pos_x,pos_y-tam);
    glEnd();

}
Bonus::~Bonus()
{
    //dtor
}

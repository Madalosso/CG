#include "Aviao.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "math.h"
#include <stdio.h>

Aviao::Aviao()
{
    pos_x=0;
    pos_y=0;
    tam=3;
    ang=0;
    subindo=false;
}

void Aviao::draw(){
    if(subindo){
        ang+=1;
    }else{
        ang-=1;
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        //glVertex2f(5,5);
        //glVertex2f(5+tam,5);
        //glVertex2f(5+0.2,5-0.5);
        glVertex2f(pos_x,pos_y);
        glVertex2f(pos_x+tam,pos_y);
        glVertex2f(pos_x+0.2,pos_y-0.5);

    glEnd();
}

Aviao::~Aviao()
{
    //dtor
}

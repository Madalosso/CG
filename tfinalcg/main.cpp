
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <Aviao.h>
#include <Bonus.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <parede.h>
#include <iomanip>
#include <locale>
#include "time.h"
#include "cstdlib"

int size_x=30,size_y=20;
int width=900,height=600;
void visualizacao(void);
Aviao aero;
float ang_speed=0.8;
bool run = true;
std::vector<parede*> lista_parede;
std::vector<Bonus*> lista_bonus;
parede wall(1,1);
int spawn_per=200,spawn_count=0,spawn_spd=1;
int bonus =0;
int per_loop=15;
int vidas=2;
float speed_obj=0.05;
int score=0;
float wait_per=100,wait_cont=0;
int mod_pt=1;
#include <sstream>
#include <string.h>
//using namespace std;
void Janela(GLint x,GLint y)
{
    glViewport(0,0,x,y);
}

void visualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,size_x,0,size_y);
}

void drawText(const char *text,int x,int y)
{
    glColor3f(1,1,1);
    glRasterPos2f(x,y);
    for(int i=0; text[i]!= '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawElements()
{
    //transformacoes para desenhar aviao inclinado
    glPushMatrix();
    glTranslatef(+aero.pos_x+aero.tam/2,+aero.pos_y,0);
    glRotatef(aero.ang, 0.0, 0.0, 1.0);
    glTranslatef(-aero.pos_x-aero.tam/2,-aero.pos_y,0);
    aero.draw();//desenha aero
    glPopMatrix();

    for(int i=0; i<lista_parede.size(); i++)
    {
        lista_parede.at(i)->draw();
    }
    for(int i=0; i<lista_bonus.size(); i++)
    {
        lista_bonus.at(i)->draw();
    }
    //print score
    char pontuacao[]="Score:";
    drawText(pontuacao,4,19);

    //print vidas
    char str_vidas[20]="";
    strcat(str_vidas,"Lifes:");
    //strcat(str_vidas,);
    std::stringstream strs;
    strs << vidas;
    std::string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();
    strcat(str_vidas,char_type);
    drawText(str_vidas,0,19);


    char print_score[]="";

    std::stringstream strs2;
    strs2 << score;
    std::string temp_str2 = strs2.str();
    char* char_type2 = (char*) temp_str2.c_str();
    strcat(print_score,char_type2);
    drawText(char_type2,6,19);
    if(!run)
    {
        char gameover[] = "Game Over! press 'r' to restart";
        drawText(gameover,10,15);

    }


}

void drawWindow()
{
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    visualizacao();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawElements();

    glFlush();
}

void setup()
{
    mod_pt=1;
    bonus=0;
    aero.pos_x = 1;
    aero.pos_y = 5;
    aero.ang=0;
    //score=0;
    wait_cont=wait_per;

    //lista_parede = new std::vector<parede>();
    lista_parede.clear();
    lista_parede.push_back(new parede(1,1));
    lista_bonus.clear();

    per_loop=15;

    spawn_count=0;
}

void restart()
{
    score=0;
    setup();
}

void Teclado(unsigned char tecla, GLint x,GLint y)
{
    switch (tecla)
    {
    case 'r':
        restart();
        run=true;
        break;
    case 'w':
        lista_parede.push_back(new parede(1,1));
        break;
    case 'b':
        lista_bonus.push_back(new Bonus());
        break;
    case 27:
        run=false;
        exit(0);
        break;
    }
}


void TecladoEspecial(GLint tecla, GLint x,GLint y)
{

    switch(tecla)
    {
    case GLUT_KEY_LEFT:
        aero.ang+=ang_speed;
        //printf("\n ang y : %f",aero.ang);
        break;
    case GLUT_KEY_RIGHT:
        aero.ang-=ang_speed;
        //printf("\n ang y : %f",aero.ang);
        break;
    case GLUT_KEY_F9:
        if(run)
        {
            run=false;
        }
        else
        {
            run=true;
        }
        break;
    }
    //drawWindow();
}

bool colisao()
{
    //printf("\n\t wall = %f , ponto frente = %f",wall.pos_x,abs(aero.pos_x+aero.tam));
    for(int i =0; i<lista_parede.size(); i++)
    {
        //printf("in");
        parede *p= lista_parede.at(i);
        //    printf("\n posicao X: %f",p->pos_x);
        if(p->pos_x<=abs(aero.pos_x+aero.tam)) //refinar pontos de colisao
        {
            if(aero.pos_y > p->gap_up || aero.pos_y< p->gap_down)
            {
                return true;
            }
        }
    }


    return false;
}

int check_bonus()
{
    for(int i=0; i<lista_bonus.size(); i++)
    {
        Bonus *b = lista_bonus.at(i);
        if(b->pos_x<=abs(aero.pos_x+aero.tam))
        {
            if(aero.pos_y<=b->pos_y && aero.pos_y>=b->pos_y-b->tam)
            {
                printf("PEGA BONUS");
                lista_bonus.erase(lista_bonus.begin()+i);
                return b->bonus;
            }
        }
    }
    return 0 ;

}

void moveParedes()
{
    for(int i=0; i<lista_parede.size(); i++)
    {
        parede *p= lista_parede.at(i);
        if(p->pos_x>0)
        {
            p->pos_x-=speed_obj;
            if(p->pos_x<0)
            {
                score+=mod_pt;
                lista_parede.erase(lista_parede.begin()+i);
            }
        }
    }
}

void moveBonus()
{
    for(int i=0; i<lista_bonus.size(); i++)
    {
        Bonus *b= lista_bonus.at(i);
        if(b->pos_x>0)
        {
            b->pos_x-=speed_obj;
            if(b->pos_x<0)
            {
                lista_bonus.erase(lista_bonus.begin()+i);
            }
        }
    }
}


void timerFunc(int value)
{
    //printf("\nloop");
    //drawWindow();
    if(run)
    {
        printf("\n Numero de walls: %d",lista_parede.size());
        //for(int i =0;i<lista_parede.size();i++){
        //     printf("\n\t %d \tpos x: %f",i+1,lista_parede.at(i)->pos_x);
        // }
        glutPostRedisplay();
        moveParedes();
        moveBonus();

        if(spawn_count<=0)
        {
            lista_parede.push_back(new parede(1,1));
            spawn_count=spawn_per;

            /*srand(time(NULL));
            int r_random = rand()%2;
            //printf("RANDOM = %d",r_random);
            switch(r_random)
            {
            case 0:
                lista_parede.push_back(new parede(1,1));
                spawn_count=spawn_per;
                break;
            case 1:
                lista_bonus.push_back(new Bonus());
                spawn_count=spawn_per;
                break;
            }
            */

        }
        printf("\n Contador : %d",spawn_count);
        spawn_count-=spawn_spd;
        // printf("\nang = %f",aero.ang);
        aero.pos_y+=aero.ang*0.01;
        bonus = check_bonus();
        wait_cont--;
        printf("\n\tcont = %f",wait_cont);
        if(wait_cont<=0&&per_loop>4)
        {
            per_loop-=1;
            wait_cont=wait_per*3;
            printf("\n\t **** SPEED ++  = %d",per_loop);
            //run=false;
        }
        if(bonus!=0)
        {
            switch(bonus)
            {
            case 1:
                if(mod_pt<4)
                {
                    mod_pt*=2;
                }
                break;
            case 2:
                score+=mod_pt;
                break;
            case 3:
                if(vidas<5)
                {
                    vidas++;
                }
                break;
            }
            bonus = 0;
        }
        if(colisao()||aero.pos_y>size_y || aero.pos_y<0)//DEAD?
        {
            if(vidas>0)
            {
                vidas--;
                setup();
            }
            else
            {
                run=false;
                printf("Game Over");

            }
            printf("\n\n\t\tBOOM HEADSHOT! COLISAO ");
        }

    }

    glutTimerFunc(per_loop,timerFunc,0);
}


void mouseClick(int button,int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
    {
        aero.subindo=true;
    }
    if(button == GLUT_LEFT_BUTTON && state ==GLUT_UP)
    {

        aero.subindo=false;
    }
    if(button == GLUT_RIGHT_BUTTON && state ==GLUT_DOWN)
    {
        speed_obj*=2;
        spawn_spd*=2;

    }
    if(button == GLUT_RIGHT_BUTTON && state ==GLUT_UP)
    {
        speed_obj/=2;
        spawn_spd/=2;
    }
}

int main (int argc, char *argv[])
{
    //std::vector<parede> lista_paredes;

    glutInitWindowSize(width,height);
    glutCreateWindow("Esse xarope me da sono");
    setup();
    //printf("pos x %f/n pos y %f",aero.pos_x,aero.pos_y);
    glutDisplayFunc(drawWindow);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TecladoEspecial);
    glutMouseFunc(mouseClick);

    //glutReshapeFunc(resize);

    glutTimerFunc(200,timerFunc,0);
    glutMainLoop();


    return 0;
}

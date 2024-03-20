/*
Programul afiseaza un patrat pe care il translateaza 
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);


static GLfloat x=0;
static GLfloat y = 0;
static GLfloat alfa = 0;
static GLUquadricObj* o;

void myinit (void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaJos(void)
{
    y = y + 10;
}
void CALLBACK MutaSus(void)
{
    y = y - 10;
}

void CALLBACK MutaStanga(void)
{
	x=x-15;
}

void CALLBACK MutaDreapta(void)
{
	x=x+10;
}
void CALLBACK RotateLeft(AUX_EVENTREC* event)
{
    alfa += 15;
}
void CALLBACK RotateRight(AUX_EVENTREC *event)
{
    alfa -= 15;
}


void CALLBACK display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();
    o = gluNewQuadric();
    glRotatef(alfa, 1, 0,0 );

    glPushMatrix();  
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluCylinder(o, 50.0, 50.0, 100,200,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x-100, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluSphere(o, 50.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+100, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluCylinder(o, 0.0, 50.0, 100, 200, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x + 200, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluDisk(o, 20.0, 50.0, 100, 200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x-200, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluDisk(o, 0.0, 50.0, 100, 200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+300, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluPartialDisk(o, 20.0, 50.0, 100,20, 0.0,90.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x - 300, y, 0.0);
    glColor3f(1.0, 0, 0);
    gluQuadricDrawStyle(o, GLU_FILL);
    gluPartialDisk(o, 0.0, 50.0, 100, 20, 0.0, 90.0);
    glPopMatrix();

    glFlush();
}


/*void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-160.0, 160.0, -160.0, 
        160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}*/

void CALLBACK myReshape(GLsizei w, GLsizei h)	
{
    if (!h) return;
    glViewport(0, 0, w, h);	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)		
    glOrtho (-500.0, 500.0, 500.0*(GLfloat)h/(GLfloat)w, 
        -500.0*(GLfloat)h/(GLfloat)w, -160.0, 160.0);
    else 
    glOrtho (-500.0*(GLfloat)w/(GLfloat)h,
        500.0*(GLfloat)w/(GLfloat)h, 500.0, 500.0, -160.0, 160.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, 300, 400);
    auxInitWindow ("Un patrat care se translateaza pe axa x");
    myinit ();
	auxKeyFunc (AUX_LEFT, MutaStanga);
	auxKeyFunc (AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, RotateLeft);
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, RotateLeft);
    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}

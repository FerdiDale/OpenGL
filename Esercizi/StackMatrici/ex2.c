#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float minutesAngle = 0;
float secondsAngle = 0;
byte stopped = 1;

void timeFunc (int value) {
    if (stopped == 0) {
        secondsAngle -= 6;
        if (secondsAngle <= (-360)) {
            minutesAngle -= 360/60;
            secondsAngle = 0;
        }
        glutPostRedisplay();
        glutTimerFunc(1000, timeFunc, 0);
    }
}

void mouseFunc (int button, int state, int x, int y) {
    printf("%d", stopped);
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (stopped == 1) {
                stopped = 0;
                glutTimerFunc(1000, timeFunc, 0);
            }
            else {
                stopped = 1;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            minutesAngle = 0;
            secondsAngle = 0;
        }
    }
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 1.0, 1.0 , 1.0);
    glVertex2f(0.0, 0.0);
    float radius = 0.7;
    float x;
    float y;
    for (int i = 0; i < 12 ; i++)
    {
        float angle = i*6.28/12;
        x = radius*cos(angle);
        y = radius*sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(0.7, 0.0);
    glEnd();

    glPushMatrix();
    glRotatef(minutesAngle, 0, 0, 1);
    glBegin( GL_POLYGON );
    glColor4f( 0.0, 1.0, 0.0 , 1.0);
    glVertex2f(-0.02, 0.0);
    glVertex2f(-0.02, 0.5);
    glVertex2f(0.02, 0.5);
    glVertex2f(0.02, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(secondsAngle, 0, 0, 1);
    glBegin( GL_POLYGON );
    glColor4f( 0.0, 0.0, 0.0 , 1.0);
    glVertex2f(-0.01, 0.0);
    glVertex2f(-0.01, 0.6);
    glVertex2f(0.01, 0.6);
    glVertex2f(0.01, 0.0);
    glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutMainLoop(); //Ciclo principale
}
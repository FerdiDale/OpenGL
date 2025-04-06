#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float hoursAngle = 0;
float minutesAngle = 0;
float downAngle;
byte pressed;

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            pressed = 1;
        }
        else {
            pressed = 0;
        }
    }
}

void motionFunc (int x, int y) {
    if (pressed) {
        minutesAngle -= 360/60;
        if (minutesAngle <= (-360)) {
            hoursAngle -= 360/12;
            minutesAngle = 0;
        }
        glutPostRedisplay();
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
    glVertex2f(-0.05, 0.0);
    glVertex2f(-0.05, 0.6);
    glVertex2f(0.05, 0.6);
    glVertex2f(0.05, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(hoursAngle, 0, 0, 1);
    glBegin( GL_POLYGON );
    glColor4f( 1.0, 0.0, 0.0 , 1.0);
    glVertex2f(-0.05, 0.0);
    glVertex2f(-0.05, 0.4);
    glVertex2f(0.05, 0.4);
    glVertex2f(0.05, 0.0);
    glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMainLoop(); //Ciclo principale
}
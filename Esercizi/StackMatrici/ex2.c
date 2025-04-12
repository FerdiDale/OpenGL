#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float minutesAngle = 0;
float secondsAngle = 0;
float angle;
byte stopped = 1, started = 0, restarted = 0;
clock_t startTime, endTime;
int timeDiff;

void keyboard (unsigned char key, int x, int y) {
    switch (key){
        case ' ':
            angle+=45;
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
    }
}

void timeFunc (int value) {
    if (started == 1 && value == 1)
        return;
    started = 1;
    if (stopped == 0) {
        if (restarted != 1) {
            secondsAngle -= 6;
            if (secondsAngle <= (-360)) {
                minutesAngle -= 360/60;
                secondsAngle = 0;
            }
            glutPostRedisplay();
            glutTimerFunc(1000, timeFunc, 0);
        }
        else {
            endTime = clock();
            timeDiff = (int)(endTime - startTime) / CLOCKS_PER_SEC * 1000;
            restarted = 0;
            glutTimerFunc(1000 - timeDiff, timeFunc, 0);
        }
    }
    else {
        started = 0;
    }
}

void mouseFunc (int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (stopped == 1) {
                stopped = 0;
                glutTimerFunc(1000, timeFunc, 1);
            }
            else {
                restarted = 0;
                stopped = 1;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            minutesAngle = 0;
            secondsAngle = 0;
            restarted = 1;
            startTime = clock();
        }
    }
}

GLvoid drawScene(GLvoid) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 1.0, 1.0, 1.0);
    float radius = 0.7;
    float x;
    float y;
    float nearZ = 0.0;
    float farZ = -0.2;
    glVertex3f(0.0, 0.0, nearZ);
    for (int i = 0; i < 12 ; i++)
    {
        float angle = i*6.28/12;
        x = radius*cos(angle);
        y = radius*sin(angle);
        glVertex3f(x, y, nearZ);
    }
    glVertex3f(0.7, 0.0, nearZ);
    glEnd();

    glBegin( GL_QUAD_STRIP );
    glColor4f( 1.0, 1.0, 0.0 , 1.0);
    glVertex3f(0.0, 0.0, nearZ);
    glVertex3f(0.0, 0.0, farZ);
    for (int i = 0; i < 12 ; i++)
    {
        float angle = i*6.28/12;
        x = radius*cos(angle);
        y = radius*sin(angle);
        glVertex3f(x, y, nearZ);
        glVertex3f(x, y, farZ);
    }
    glVertex3f(0.7, 0.0, nearZ);
    glVertex3f(0.7, 0.0, farZ);
    glEnd();

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, farZ);
    for (int i = 0; i < 12 ; i++)
    {
        float angle = i*6.28/12;
        x = radius*cos(angle);
        y = radius*sin(angle);
        glVertex3f(x, y, farZ);
    }
    glVertex3f(0.7, 0.0, farZ);
    glEnd();

    glPushMatrix();
    glRotatef(minutesAngle, 0, 0, 1);
    glBegin( GL_POLYGON );
    glColor4f( 0.0, 1.0, 0.0 , 1.0);
    glVertex3f(-0.02, 0.0, nearZ+0.001);
    glVertex3f(-0.02, 0.5, nearZ+0.001);
    glVertex3f(0.02, 0.5, nearZ+0.001);
    glVertex3f(0.02, 0.0, nearZ+0.001);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(secondsAngle, 0, 0, 1);
    glBegin( GL_POLYGON );
    glColor4f( 0.0, 0.0, 0.0 , 1.0);
    glVertex3f(-0.01, 0.0, nearZ+0.001);
    glVertex3f(-0.01, 0.6, nearZ+0.001);
    glVertex3f(0.01, 0.6, nearZ+0.001);
    glVertex3f(0.01, 0.0, nearZ+0.001);
    glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize ( 500, 500 );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //Ciclo principale
}
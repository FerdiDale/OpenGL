#include <GL/gl.h> //Inclusione libreria GL
#include <GL/glu.h>
#include <GL/glut.h> //Inclusione libreria GLU
#include <time.h>
#include <stdio.h>
#include <math.h>

float posX = 0, posY = 0;
float angle = 0, scaleX = 1, scaleY = 1;
int windowWidth = 500, windowHeight = 500;
int rotating = 0, scaling = 0;
float pressX, pressY;
float baseScaleX, baseScaleY, baseAngle;

float getRelativeX (float pointerX) {
    return (pointerX/windowWidth*2)-1;
}

float getRelativeY (float pointerY) {
    return (pointerY/windowHeight*(-2))+1;
}

void mouseCallback (int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        pressX = x;
        pressY = y;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        rotating = 1;
        baseAngle = angle;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
        rotating = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        scaling = 1;
        baseScaleX = scaleX;
        baseScaleY = scaleY;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
        scaling = 0;
}

void passiveMotionCallback (int x, int y) {
    posX = getRelativeX(x);
    posY = getRelativeY(y);
    glutPostRedisplay();
}

void motionCallback (int x, int y) {
    if (rotating) {
        angle = baseAngle + acos(getRelativeX(x))/3.14*180;
    }
    else if (scaling) {
        scaleX = baseScaleX + (getRelativeX(x)-getRelativeX(pressX));
        scaleY = baseScaleY + (getRelativeY(y)-getRelativeY(pressY));
    }
    glutPostRedisplay();
}

GLvoid drawScene(GLvoid) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(posX, posY, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, 1);

    glBegin( GL_TRIANGLE_FAN );
    glColor4f( 1.0, 1.0, 1.0 , 1.0);
    glVertex2f(0.0, 0.0);
    float radius;
    for (int i = 0; i < 10 ; i++)
    {
        if (i%2==0)
            radius = 0.15;
        else
            radius = 0.7;
        float angle = i*6.28/10;
        float x = radius*cos(angle);
        float y = radius*sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(0.15, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize ( windowWidth, windowHeight );
    glutCreateWindow("Esercizio"); //Creazione finestra
    glutDisplayFunc(drawScene); //Richiamo funzione di disegno
    glutMotionFunc(motionCallback);
    glutPassiveMotionFunc(passiveMotionCallback);
    glutMouseFunc(mouseCallback);
    glutMainLoop(); //Ciclo principale
}